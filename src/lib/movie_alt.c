/* TMDB - TheMovieDB web api library
* Copyright (C) 2012 Atanas Tulbenski <top4e@top4e.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library;
* if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tmdb.h"

#include "movie_alt.h"

static int movie_alt_parse(jsmntok_t *tok, size_t cnt, char *data, void *udata)
{
	int i = 0;
	tmdb_movie_t **movie_alt = (tmdb_movie_t **)udata;
	tmdb_movie_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "id")), -1);
	i++;
	CHK((token_str_cmp(data, &tok[i++], "titles")), -1);
	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*movie_alt = malloc(sizeof(tmdb_movie_t));
		info = *movie_alt;
		memset(info, 0, sizeof(tmdb_movie_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		info->production_countries = malloc(sizeof(tmdb_country_t));
		memset(info->production_countries, 0, sizeof(tmdb_country_t));
		CPTAGT(JSMN_STRING, "iso_3166_1",
		       &info->production_countries->iso_3166_1);
		CPTAG(JSMN_STRING,  "title",      &info->title);

		movie_alt = &info->next;
	}

	return 0;
}
/*
	MOVIE / ALTERNATIVE TITLES
*/
tmdb_movie_t *tmdb_movie_alt_titles(const char *movie_id, const char *country)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_t		*info = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_ALT_TITLES;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);
	if (country)
		tmdb_ctx_set(&ctx, COUNTRY, country);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_ALT_NUM_TOKENS,
			     movie_alt_parse, &info);
	}
	free_data_chunk(&data);

	return info;
}
