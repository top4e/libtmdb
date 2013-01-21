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

#include "search_company.h"

static int company_search_parse(jsmntok_t	*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_company_t **company = (tmdb_company_t **)udata;
	tmdb_company_t *info;
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
		*company = malloc(sizeof(tmdb_company_t));
		info = *company;
		memset(info, 0, sizeof(tmdb_company_t));
		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "id",           &info->id);
		CPTAG(JSMN_STRING,     "logo_path",    &info->logo_path);
		CPTAGT(JSMN_STRING,    "name",         &info->name);
		company = &info->next;
	}
	return 0;
}

/*
	SEARCH / COMPANY
*/
tmdb_company_t *tmdb_search_company(const char *name)
{
	int			result;
	char			*url_str;
	char			*esc_name;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_company_t		*companies = NULL;

	init_data_chunk(&data);

	esc_name = escaped_string(name);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = SEARCH_COMPANY;
	tmdb_ctx_set(&ctx, QUERY, esc_name);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);
	free(esc_name);

	if (!result) {
		header_process(&data);
		body_process(&data, SEARCH_COMPANY_NUM_TOKENS,
			     company_search_parse, &companies);
	}
	free_data_chunk(&data);

	return companies;
}
