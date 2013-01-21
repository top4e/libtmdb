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

#include "auth_new_token.h"

#define DBG_AUTH_NEW_TOKEN

#ifdef DBG_AUTH_NEW_TOKEN
static void dump_token(auth_token_t *token)
{
	printf("expires_at   : %s\n", token->expires_at);
	printf("request_token: %s\n", token->token);
}
#endif

static int auth_token_parse(jsmntok_t *tok, size_t cnt, char *data, void *udata)
{
	int i = 0;
	auth_token_t *token = (auth_token_t *)udata;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "success")), -1);

	CHK((tok[i].type != JSMN_PRIMITIVE), -1);
	CHK((token_str_cmp(data, &tok[i++], "true")), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "expires_at")), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	token_str_cpy(data, &tok[i++], &token->expires_at);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "request_token")), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	token_str_cpy(data, &tok[i++], &token->token);

	return 0;
}

/*
	AUTHORIZATION / NEW TOKEN
*/

auth_token_t *tmdb_auth_new_token(void)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	auth_token_t		*token = NULL;

	token = malloc(sizeof(auth_token_t));

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = AUTH_TOKEN_NEW;

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, AUTH_NEW_TOKEN_NUM_TOKENS,
			     auth_token_parse, token);
	}
	free_data_chunk(&data);
#ifdef DBG_AUTH_NEW_TOKEN
	dump_token(token);
#endif
	return token;
}
