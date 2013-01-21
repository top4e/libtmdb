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

#include "collection_info.h"

static int collection_info_parse(jsmntok_t *tok,
				 size_t cnt,
				 char *data,
				 void *udata)
{
	int i = 0;
	tmdb_collection_t **collection = (tmdb_collection_t **)udata;
	tmdb_movie_t	   **parts;
	tmdb_movie_t	   *part;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*collection = malloc(sizeof(tmdb_collection_t));
	memset(*collection, 0, sizeof(tmdb_collection_t));

	CPTAGT(JSMN_PRIMITIVE, "id",         &((*collection)->id));
	CPTAGT(JSMN_STRING, "name",          &((*collection)->name));
	CPTAGT(JSMN_STRING, "poster_path",   &((*collection)->poster_path));
	CPTAGT(JSMN_STRING, "backdrop_path", &((*collection)->backdrop_path));

	CHK((token_str_cmp(data, &tok[i++], "parts")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	parts = &((*collection)->parts);

	for (; count--;) {
		*parts = malloc(sizeof(tmdb_movie_t));
		part = *parts;
		memset(part, 0, sizeof(tmdb_movie_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING,    "title",         &part->title);
		CPTAGT(JSMN_PRIMITIVE, "id",            &part->id);
		CPTAGT(JSMN_STRING,    "release_date",  &part->release_date);
		CPTAGT(JSMN_STRING,    "poster_path",   &part->poster_path);
		CPTAGT(JSMN_STRING,    "backdrop_path", &part->backdrop_path);

		parts = &part->next;
	}

	return 0;
}
/*
	COLLECTION / INFO
*/
tmdb_collection_t *tmdb_collection_info(const char *collection_id,
					const char *language)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_collection_t	*collection_info = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = COLLECTION;
	tmdb_ctx_set(&ctx, COLLECTION_ID, collection_id);
	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, COLLECTION_INFO_NUM_TOKENS,
			     collection_info_parse, &collection_info);
	}
	free_data_chunk(&data);

	return collection_info;
}
