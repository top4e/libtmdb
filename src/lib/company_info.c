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

#include "company_info.h"


static int company_info_parse(jsmntok_t	*tok,
			      size_t	cnt,
			      char	*data,
			      void	*udata)
{
	int i = 0;
	tmdb_company_t **company = (tmdb_company_t **)udata;
	tmdb_company_t *info;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*company = malloc(sizeof(tmdb_company_t));
	info = *company;
	memset(info, 0, sizeof(tmdb_company_t));

	CPTAG(JSMN_STRING,     "description",  &info->description);
	CPTAG(JSMN_STRING,     "headquarters", &info->headquarters);
	CPTAG(JSMN_STRING,     "homepage",     &info->homepage);
	CPTAGT(JSMN_PRIMITIVE, "id",           &info->id);
	CPTAG(JSMN_STRING,     "logo_path",    &info->logo_path);
	CPTAGT(JSMN_STRING,    "name",         &info->name);
	CHK(token_str_cmp(data, &tok[i++], "parent_company"), -1);

	if (tok[i++].type == JSMN_OBJECT) {
		company = &info->parent_company;
		*company = malloc(sizeof(tmdb_company_t));
		info = *company;
		memset(info, 0, sizeof(tmdb_company_t));

		CPTAGT(JSMN_STRING,    "name",         &info->name);
		CPTAGT(JSMN_PRIMITIVE, "id",           &info->id);
		CPTAG(JSMN_STRING,     "logo_path",    &info->logo_path);
	}

	return 0;
}

/*
	COMPANY / INFO
*/
tmdb_company_t *tmdb_company_info(const char *company_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_company_t		*companies = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = COMPANY;
	if (company_id)
		tmdb_ctx_set(&ctx, COMPANY_ID, company_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, COMPANY_INFO_NUM_TOKENS,
			     company_info_parse, &companies);
	}
	free_data_chunk(&data);

	return companies;
}
