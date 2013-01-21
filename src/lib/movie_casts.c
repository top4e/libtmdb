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

#include "movie_casts.h"

static int movie_casts_parse(jsmntok_t *tok,
			     size_t cnt,
			     char *data,
			     void *udata)
{
	int i = 0;
	tmdb_movie_casts_t **movie_casts = (tmdb_movie_casts_t **)udata;
	tmdb_cast_t	   **casts;
	tmdb_cast_t	   *cast;
	tmdb_crew_t	   **crews;
	tmdb_crew_t	   *crew;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*movie_casts = malloc(sizeof(tmdb_movie_casts_t));
	memset(*movie_casts, 0, sizeof(tmdb_movie_casts_t));

	CPTAGT(JSMN_PRIMITIVE, "id", &((*movie_casts)->id));

	CHK((token_str_cmp(data, &tok[i++], "cast")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	casts = &((*movie_casts)->cast);
	for (; count--;) {
		*casts = malloc(sizeof(tmdb_cast_t));
		cast = *casts;
		memset(cast, 0, sizeof(tmdb_cast_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id", &cast->id);
		CPTAGT(JSMN_STRING,    "name",         &cast->name);
		CPTAGT(JSMN_STRING,    "character",    &cast->character);
		CPTAGT(JSMN_PRIMITIVE, "order",        &cast->order);
		CPTAGT(JSMN_PRIMITIVE, "cast_id",      &cast->cast_id);
		CPTAG(JSMN_STRING,     "profile_path", &cast->profile_path);
		casts = &cast->next;
	}

	CHK((token_str_cmp(data, &tok[i++], "crew")), -1);

	crews = &((*movie_casts)->crew);
	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*crews = malloc(sizeof(tmdb_crew_t));
		crew = *crews;
		memset(crew, 0, sizeof(tmdb_crew_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id",           &crew->id);
		CPTAGT(JSMN_STRING,    "name",         &crew->name);
		CPTAG(JSMN_STRING,     "department",   &crew->department);
		CPTAG(JSMN_STRING,     "job",          &crew->job);
		CPTAG(JSMN_STRING,     "profile_path", &crew->profile_path);

		crews = &crew->next;
	}

	return 0;
}
/*
	MOVIE / CASTS
*/
tmdb_movie_casts_t *tmdb_movie_casts(const char *movie_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_casts_t	*movie_casts = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_CASTS;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_CASTS_NUM_TOKENS,
			     movie_casts_parse, &movie_casts);
	}
	free_data_chunk(&data);

	return movie_casts;
}
