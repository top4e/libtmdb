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
* if not, see <http://www.gnu.org/licenses/>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tmdb.h"

#include "configuration.h"

/*
	CONFIGURATION
*/

static int tmdb_get_sizes(jsmntok_t *tok,
			  size_t idx,
			  char *data,
			  char *name,
			  char ***sizes,
			  int *count)
{
	int j;
	int cnt = 0;

	CHK((tok[idx].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[idx++], name)), -1);
	CHK((tok[idx].type != JSMN_ARRAY), -1);
	j = idx++;

	while (tok[idx].parent == j) {
		if (*sizes == NULL)
			*sizes = malloc(sizeof(char *));
		else
			*sizes = realloc(*sizes, sizeof(char *) * (idx-j));

		CHK((tok[idx].type != JSMN_STRING), -1);
		token_str_cpy(data, &tok[idx], &((*sizes)[idx-j-1]));
		cnt++;
		idx++;
	}
	*count = cnt;
	return idx;
}

static int tmdb_parse_cfg(jsmntok_t *tok, size_t cnt, char *data, void *udata)
{
	int			i = 0;
	tmdb_configuration_t	**cfg = (tmdb_configuration_t **)udata;
	tmdb_configuration_t	*info;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((tok[i].type != JSMN_STRING), -1);

	CHK((token_str_cmp(data, &tok[i++], "images")), -1);

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*cfg = malloc(sizeof(tmdb_configuration_t));
	memset(*cfg, 0, sizeof(tmdb_configuration_t));
	info = *cfg;

	CPTAGT(JSMN_STRING,     "base_url",  &info->base_url);
	CPTAGT(JSMN_STRING,     "secure_base_url",  &info->secure_base_url);

	/* poster sizes */
	i = tmdb_get_sizes(tok, i, data, "poster_sizes",
			   &info->poster_sizes, &info->poster_sizes_cnt);
	/* backdrop sizes */
	i = tmdb_get_sizes(tok, i, data, "backdrop_sizes",
			   &info->backdrop_sizes, &info->backdrop_sizes_cnt);
	/* profile sizes */
	i = tmdb_get_sizes(tok, i, data, "profile_sizes",
			   &info->profile_sizes, &info->profile_sizes_cnt);
	/* logo sizes */
	i = tmdb_get_sizes(tok, i, data, "logo_sizes",
			   &info->logo_sizes, &info->logo_sizes_cnt);

	return 0;
}

tmdb_configuration_t *tmdb_configuration(void)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_configuration_t	*cfg = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = CONFIGURATION;

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, CONFIGURATION_NUM_TOKENS,
			     tmdb_parse_cfg, &cfg);
	}
	free_data_chunk(&data);

	return cfg;
}
