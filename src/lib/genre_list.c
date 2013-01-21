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

#include "genre_list.h"

static int genre_list_parse(jsmntok_t	*tok,
			    size_t	cnt,
			    char	*data,
			    void	*udata)
{
	int i = 0;
	tmdb_genre_t **genre = (tmdb_genre_t **)udata;
	tmdb_genre_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);
	CHK((tok[i].type != JSMN_STRING), -1);
	CHK(token_str_cmp(data, &tok[i++], "genres"), -1);

	if (tok[i].type == JSMN_ARRAY) {
		count = tok[i].size;
		i++;
	}

	CHK(!count, -1);

	for (; count--;) {
		*genre = malloc(sizeof(tmdb_genre_t));
		info = *genre;
		memset(info, 0, sizeof(tmdb_genre_t));
		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id",           &info->id);
		CPTAG(JSMN_STRING,    "name",         &info->name);
		genre = &info->next;
	}
	return 0;
}

/*
	GENRE / LIST
*/
tmdb_genre_t *tmdb_genre_list(const char *language)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_genre_t		*genres = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = GENRE_LIST;
	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, GENRE_LIST_NUM_TOKENS,
			     genre_list_parse, &genres);
	}
	free_data_chunk(&data);

	return genres;
}
