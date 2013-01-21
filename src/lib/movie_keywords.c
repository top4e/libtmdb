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

#include "movie_keywords.h"

static int movie_keywords_parse(jsmntok_t	*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_movie_keywords_t **movie_keywords =
				(tmdb_movie_keywords_t **)udata;
	tmdb_keywords_t	   **keywords;
	tmdb_keywords_t	   *keyword;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*movie_keywords = malloc(sizeof(tmdb_movie_keywords_t));
	memset(*movie_keywords, 0, sizeof(tmdb_movie_keywords_t));

	CPTAGT(JSMN_PRIMITIVE, "id", &((*movie_keywords)->id));

	CHK((token_str_cmp(data, &tok[i++], "keywords")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	keywords = &((*movie_keywords)->keywords);
	for (; count--;) {
		*keywords = malloc(sizeof(tmdb_keywords_t));
		keyword = *keywords;
		memset(keyword, 0, sizeof(tmdb_keywords_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id",   &keyword->id);
		CPTAGT(JSMN_STRING,    "name", &keyword->name);

		keywords = &keyword->next;
	}

	return 0;
}
/*
MOVIE / GET_IMAGES
*/
tmdb_movie_keywords_t *tmdb_movie_keywords(const char *movie_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_keywords_t	*movie_keywords = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_KEYWORDS;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_KEYWORDS_NUM_TOKENS,
			     movie_keywords_parse, &movie_keywords);
	}
	free_data_chunk(&data);

	return movie_keywords;
}
