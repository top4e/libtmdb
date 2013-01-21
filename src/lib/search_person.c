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

#include "search_person.h"

static int person_search_parse(jsmntok_t	*tok,
			       size_t		cnt,
			       char		*data,
			       void		*udata)
{
	int i = 0;
	tmdb_person_t **person = (tmdb_person_t **)udata;
	tmdb_person_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);
	i += 3;

	if (tok[i].type == JSMN_OBJECT)
		count = 1;

	if (tok[i].type == JSMN_ARRAY) {
		count = tok[i].size;
		i++;
	}

	for (; count--;) {
		*person = malloc(sizeof(tmdb_person_t));
		info = *person;
		memset(info, 0, sizeof(tmdb_person_t));
		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "adult",        &info->adult);
		CPTAGT(JSMN_PRIMITIVE, "id",           &info->id);
		CPTAGT(JSMN_STRING,    "name",         &info->name);
		CPTAG(JSMN_STRING,     "profile_path", &info->profile_path);
		person = &info->next;
	}

	return 0;
}
/*
	SEARCH / PERSON
*/
tmdb_person_t *tmdb_search_person(const char *name, int adult)
{
	int			result;
	char			*url_str;
	char			*esc_name;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_person_t		*persons = NULL;

	init_data_chunk(&data);
	esc_name = escaped_string(name);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = SEARCH_PERSON;
	tmdb_ctx_set(&ctx, QUERY, esc_name);

	if (adult)
		tmdb_ctx_set(&ctx, INCLUDE_ADULT, "true");

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);
	free(esc_name);

	if (!result) {
		header_process(&data);
		body_process(&data, SEARCH_PERSON_NUM_TOKENS,
			     person_search_parse, &persons);
	}
	free_data_chunk(&data);

	return persons;
}
