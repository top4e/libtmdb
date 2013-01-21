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

#include "person_latest.h"

static int person_latest_parse(jsmntok_t	*tok,
			       size_t		cnt,
			       char		*data,
			       void		*udata)
{
	int i = 0;
	tmdb_person_t **person = (tmdb_person_t **)udata;
	tmdb_person_t *info;
	int count = 0;
	int idx;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*person = malloc(sizeof(tmdb_person_t));
	info = *person;
	memset(info, 0, sizeof(tmdb_person_t));

	CPTAGT(JSMN_PRIMITIVE, "adult",          &info->adult);

	CHK((token_str_cmp(data, &tok[i++], "also_known_as")), -1);
	CHK((tok[i].type != JSMN_ARRAY), -1);
	count = tok[i++].size;

	if (count) {
		idx = 0;
		info->also_known_as = malloc(sizeof(char *) * count);
		while (count--) {
			CHK((tok[i].type != JSMN_STRING), -1);
			token_str_cpy(data, &tok[i++],
				      &info->also_known_as[idx++]);
		}
	}

	CPTAG(JSMN_STRING,     "biography",      &info->biography);
	CPTAG(JSMN_STRING,     "birthday",       &info->birthday);
	CPTAG(JSMN_STRING,     "deathday",       &info->deathday);
	CPTAG(JSMN_STRING,     "homepage",       &info->homepage);
	CPTAGT(JSMN_PRIMITIVE, "id",             &info->id);
	CPTAGT(JSMN_STRING,    "name",           &info->name);
	CPTAG(JSMN_STRING,     "place_of_birth", &info->place_of_birth);
	CPTAG(JSMN_STRING,     "profile_path",   &info->profile_path);

	return 0;
}

/*
	PERSON / GET LATEST ADDED
*/
tmdb_person_t *tmdb_person_latest(void)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_person_t		*person = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = PERSON_LATEST;

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, PERSON_LATEST_NUM_TOKENS,
			     person_latest_parse, &person);
	}
	free_data_chunk(&data);

	return person;
}
