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

#include "person_credits.h"

static int person_credits_parse(jsmntok_t	*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_person_credits_t **credits = (tmdb_person_credits_t **)udata;
	tmdb_person_credits_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "cast")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*credits = malloc(sizeof(tmdb_person_credits_t));
		info = *credits;
		memset(info, 0, sizeof(tmdb_person_credits_t));
		info->movie = malloc(sizeof(tmdb_movie_t));
		memset(info->movie, 0, sizeof(tmdb_movie_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id",
		       &info->movie->id);
		CPTAG(JSMN_STRING,     "title",
		      &info->movie->title);
		CPTAG(JSMN_STRING,     "character",
		      &info->character);
		CPTAG(JSMN_STRING,     "original_title",
		      &info->movie->original_title);
		CPTAG(JSMN_STRING,     "poster_path",
		      &info->movie->poster_path);
		CPTAG(JSMN_STRING,     "release_date",
		      &info->movie->release_date);
		CPTAG(JSMN_STRING,     "adult",
		      &info->movie->adult);

		credits = &info->next;
	}

	return 0;
}

/*
	PERSON / CREDITS
*/
tmdb_person_credits_t *tmdb_person_credits(const char *person_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_person_credits_t	*person_credits = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = PERSON_CREDITS;
	tmdb_ctx_set(&ctx, PERSON_ID, person_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, PERSON_CREDITS_NUM_TOKENS,
			     person_credits_parse, &person_credits);
	}
	free_data_chunk(&data);

	return person_credits;
}
