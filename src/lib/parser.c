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
#include "parser.h"
#include "jsmn.h"

static char *field_str_get(tmdb_fields_t field)
{
	char *ret = NULL;

	switch (field) {
	case API_HEADER_F:
	case API_URL_F:
	case API_KEY_F:
		break;
	case PAGE:
		ret = "&page=";
		break;
	case QUERY:
		ret = "&query=";
		break;
	case LANGUAGE:
		ret = "&language=";
		break;
	case INCLUDE_ADULT:
		ret = "&include_adult=";
		break;
	case REQUEST_TOKEN:
		ret = "&request_token=";
		break;
	case SESSION_ID:
		ret = "&session_id=";
		break;
	case MOVIE_ID:
		break;
	case FAVORITE:
		ret = "&favorite=";
		break;
	case MOVIE_WATCHLIST:
		ret = "&movie_watchlist=";
		break;
	case APPEND_TO_RESPONSE:
		ret = "append_to_response=";
		break;
	case COUNTRY:
		ret = "&country=";
		break;
	case VALUE:
		ret = "&value=";
		break;
	case YEAR:
		ret = "&year=";
		break;
	case START_DATE:
		ret = "&start_date=";
		break;
	case END_DATE:
		ret = "&end_date=";
		break;
	case GENRE_ID:
		break;
	case COLLECTION_ID:
		break;
	case PERSON_ID:
		break;
	case COMPANY_ID:
		break;
	default:
		break;
	}
	return ret;
}

#if 0
static tmdb_method_t method_fields[] = {
{ CONFIGURATION,	NONE						},

{ AUTH_TOKEN_NEW,	NONE						},
{ AUTH_SESSION_NEW,	REQUEST_TOKEN					},

{ ACOUNT,		SESSION_ID					},
{ ACOUNT_FAV_MOVIES,	SESSION_ID | PAGE | LANGUAGE			},
{ ACOUNT_FAV,		SESSION_ID | MOVIE_ID | FAVORITE		},
{ ACOUNT_RATED,		SESSION_ID | PAGE | LANGUAGE			},
{ ACOUNT_WATCHLIST,	SESSION_ID | PAGE | LANGUAGE			},

{ MOVIE,		MOVIE_ID | LANGUAGE | APPEND_TO_RESPONSE	},
{ MOVIE_ALT_TITLES,	MOVIE_ID | COUNTRY | APPEND_TO_RESPONSE		},
{ MOVIE_CASTS,		MOVIE_ID | APPEND_TO_RESPONSE			},
{ MOVIE_IMAGES,		MOVIE_ID | LANGUAGE | APPEND_TO_RESPONSE	},
{ MOVIE_KEYWORDS,	MOVIE_ID | APPEND_TO_RESPONSE			},
{ MOVIE_RELEASES,	MOVIE_ID | APPEND_TO_RESPONSE			},
{ MOVIE_TRAILERS,	MOVIE_ID | APPEND_TO_RESPONSE			},
{ MOVIE_TRANSLATIONS,	MOVIE_ID | APPEND_TO_RESPONSE			},
{ MOVIE_SIMILAR,	MOVIE_ID | PAGE | LANGUAGE | APPEND_TO_RESPONSE	},
{ MOVIE_CHANGES,	MOVIE_ID					},
{ MOVIE_LATEST,		NONE						},
{ MOVIE_UPCOMING,	PAGE | LANGUAGE					},
{ MOVIE_NOW_PLAYING,	PAGE | LANGUAGE					},
{ MOVIE_POPULAR,	PAGE | LANGUAGE					},
{ MOVIE_TOP_RATED,	PAGE | LANGUAGE					},
{ MOVIE_RATING,		VALUE						},

{ COLLECTION,		COLLECTION_ID | LANGUAGE | APPEND_TO_RESPONSE	},
{ COLLECTION_IMAGES,	COLLECTION_ID | LANGUAGE | APPEND_TO_RESPONSE	},

{ PERSON,		PERSON_ID | APPEND_TO_RESPONSE			},
{ PERSON_CREDITS,	PERSON_ID | LANGUAGE | APPEND_TO_RESPONSE	},
{ PERSON_IMAGES,	PERSON_ID					},
{ PERSON_CHANGES,	PERSON_ID					},
{ PERSON_LATEST,	NONE						},

{ COMPANY,		COMPANY_ID | APPEND_TO_RESPONSE			},
{ COMPANY_MOVIES,	COMPANY_ID | PAGE | LANGUAGE | APPEND_TO_RESPONSE},

{ GENRE_LIST,		LANGUAGE					},
{ GENRE_MOVIES,		GENRE_ID | PAGE | LANGUAGE			},

{ SEARCH_MOVIE,		QUERY | PAGE | LANGUAGE | INCLUDE_ADULT | YEAR	},
{ SEARCH_PERSON,	QUERY | PAGE | INCLUDE_ADULT			},
{ SEARCH_COMPANY,	QUERY | PAGE					},
};
#endif
int tmdb_ctx_set(tmdb_request_ctx_t *ctx, tmdb_fields_t field, const char *data)
{
	if (!ctx)
		return 1;

	switch (field) {
	case API_HEADER_F:
		if (!data)
			ctx->api_header = strdup(API_HEADER);
		else
			ctx->page = strdup(data);
		break;
	case API_URL_F:
		if (!data)
			ctx->api_url = strdup(API_URL);
		else
			ctx->page = strdup(data);
		break;
	case API_KEY_F:
		if (!data) {
			tmdb_ctx_t *itmdbctx;
			itmdbctx = tmdb_get_ctx();
			if (itmdbctx->api_key)
				ctx->api_key = strdup(itmdbctx->api_key);
		} else
			ctx->page = strdup(data);
		break;
	case PAGE:
		if (!data)
			return 1;
		ctx->page = strdup(data);
		break;
	case QUERY:
		if (!data)
			return 1;
		ctx->query = strdup(data);
		break;
	case LANGUAGE:
		if (!data)
			return 1;
		ctx->language = strdup(data);
		break;
	case INCLUDE_ADULT:
		if (!data)
			return 1;
		ctx->include_adult = strdup(data);
		break;
	case REQUEST_TOKEN:
		if (!data)
			return 1;
		ctx->request_token = strdup(data);
		break;
	case SESSION_ID:
		if (!data)
			return 1;
		ctx->session_id = strdup(data);
		break;
	case MOVIE_ID:
		if (!data)
			return 1;
		ctx->movie_id = strdup(data);
		break;
	case FAVORITE:
		if (!data)
			return 1;
		ctx->favorite = strdup(data);
		break;
	case MOVIE_WATCHLIST:
		if (!data)
			return 1;
		ctx->movie_watchlist = strdup(data);
		break;
	case APPEND_TO_RESPONSE:
		if (!data)
			return 1;
		ctx->append_to_response = strdup(data);
		break;
	case COUNTRY:
		if (!data)
			return 1;
		ctx->country = strdup(data);
		break;
	case VALUE:
		if (!data)
			return 1;
		ctx->value = strdup(data);
		break;
	case YEAR:
		if (!data)
			return 1;
		ctx->year = strdup(data);
		break;
	case START_DATE:
		if (!data)
			return 1;
		ctx->start_date = strdup(data);
		break;
	case END_DATE:
		if (!data)
			return 1;
		ctx->end_date = strdup(data);
		break;
	case GENRE_ID:
		if (!data)
			return 1;
		ctx->genre_id = strdup(data);
		break;
	case COLLECTION_ID:
		if (!data)
			return 1;
		ctx->collection_id = strdup(data);
		break;
	case PERSON_ID:
		if (!data)
			return 1;
		ctx->person_id = strdup(data);
		break;
	case COMPANY_ID:
		if (!data)
			return 1;
		ctx->company_id = strdup(data);
		break;
	default:
		break;
	}
	ctx->request_type.fields |= field;
	return 0;
}

char *tmdb_ctx_get(tmdb_request_ctx_t *ctx, tmdb_fields_t field)
{
	char *res = NULL;

	if (!(ctx->request_type.fields & field))
		return NULL;

	switch (field) {
	case API_HEADER_F:
		res = ctx->api_header;
		break;
	case API_URL_F:
		res = ctx->api_url;
		break;
	case API_KEY_F:
		res = ctx->api_key;
		break;
	case PAGE:
		res = ctx->page;
		break;
	case QUERY:
		res = ctx->query;
		break;
	case LANGUAGE:
		res = ctx->language;
		break;
	case INCLUDE_ADULT:
		res = ctx->include_adult;
		break;
	case REQUEST_TOKEN:
		res = ctx->request_token;
		break;
	case SESSION_ID:
		res = ctx->session_id;
		break;
	case MOVIE_ID:
		res = ctx->movie_id;
		break;
	case FAVORITE:
		res = ctx->favorite;
		break;
	case MOVIE_WATCHLIST:
		res = ctx->movie_watchlist;
		break;
	case APPEND_TO_RESPONSE:
		res = ctx->append_to_response;
		break;
	case COUNTRY:
		res = ctx->country;
		break;
	case VALUE:
		res = ctx->value;
		break;
	case YEAR:
		res = ctx->year;
		break;
	case START_DATE:
		res = ctx->start_date;
		break;
	case END_DATE:
		res = ctx->end_date;
		break;
	case GENRE_ID:
		res = ctx->genre_id;
		break;
	case COLLECTION_ID:
		res = ctx->collection_id;
		break;
	case PERSON_ID:
		res = ctx->person_id;
		break;
	case COMPANY_ID:
		res = ctx->company_id;
		break;
	default:
		break;
	}
	return res;
}

void free_ctx(tmdb_request_ctx_t *ctx)
{
	char *p;

	p = ctx->api_header;
	if (p)
		free(p);
	p = ctx->api_url;
	if (p)
		free(p);
	p = ctx->api_key;
	if (p)
		free(p);
	p = ctx->page;
	if (p)
		free(p);
	p = ctx->query;
	if (p)
		free(p);
	p = ctx->language;
	if (p)
		free(p);
	p = ctx->include_adult;
	if (p)
		free(p);
	p = ctx->request_token;
	if (p)
		free(p);
	p = ctx->session_id;
	if (p)
		free(p);
	p = ctx->movie_id;
	if (p)
		free(p);
	p = ctx->favorite;
	if (p)
		free(p);
	p = ctx->movie_watchlist;
	if (p)
		free(p);
	p = ctx->append_to_response;
	if (p)
		free(p);
	p = ctx->country;
	if (p)
		free(p);
	p = ctx->value;
	if (p)
		free(p);
	p = ctx->year;
	if (p)
		free(p);
	p = ctx->start_date;
	if (p)
		free(p);
	p = ctx->end_date;
	if (p)
		free(p);
	p = ctx->genre_id;
	if (p)
		free(p);
	p = ctx->collection_id;
	if (p)
		free(p);
	p = ctx->person_id;
	if (p)
		free(p);
	p = ctx->company_id;
	if (p)
		free(p);

	memset(ctx, 0, sizeof(tmdb_request_ctx_t));
}

const char *tmdb_method_type2str[] = {
	TMDB_CONFIGURATION,

	TMDB_AUTH_TOKEN_NEW,
	TMDB_AUTH_SESSION_NEW,

	TMDB_ACOUNT,
	TMDB_ACOUNT_FAV_MOVIES,
	TMDB_ACOUNT_FAV,
	TMDB_ACOUNT_RATED,
	TMDB_ACOUNT_WATCHLIST,

	TMDB_MOVIE,
	TMDB_MOVIE_ALT_TITLES,
	TMDB_MOVIE_CASTS,
	TMDB_MOVIE_IMAGES,
	TMDB_MOVIE_KEYWORDS,
	TMDB_MOVIE_RELEASES,
	TMDB_MOVIE_TRAILERS,
	TMDB_MOVIE_TRANSLATIONS,
	TMDB_MOVIE_SIMILAR,
	TMDB_MOVIE_CHANGES,
	TMDB_MOVIE_LATEST,
	TMDB_MOVIE_UPCOMING,
	TMDB_MOVIE_NOW_PLAYING,
	TMDB_MOVIE_POPULAR,
	TMDB_MOVIE_TOP_RATED,
	TMDB_MOVIE_RATING,

	TMDB_COLLECTION,
	TMDB_COLLECTION_IMAGES,

	TMDB_PERSON,
	TMDB_PERSON_CREDITS,
	TMDB_PERSON_IMAGES,
	TMDB_PERSON_CHANGES,
	TMDB_PERSON_LATEST,

	TMDB_COMPANY,
	TMDB_COMPANY_MOVIES,

	TMDB_GENRE_LIST,
	TMDB_GENRE_MOVIES,

	TMDB_SEARCH_MOVIE,
	TMDB_SEARCH_PERSON,
	TMDB_SEARCH_COMPANY,
};

char *replace(const char *original,
	      const char *pattern,
	      const char *replacement)
{
	size_t replen = strlen(replacement);
	size_t patlen = strlen(pattern);
	size_t orilen = strlen(original);
	size_t skplen;
	size_t patcnt = 0;
	const char *oriptr;
	char *patloc;
	char *retptr;

	oriptr = original;

	while (1) {
		patloc = strstr(oriptr, pattern);
		if (!patloc)
			break;
		oriptr = patloc + patlen;
		patcnt++;
	}

	size_t retlen = orilen + patcnt * (replen - patlen);
	char * returned = (char *)malloc(sizeof(char) * (retlen + 1));

	if (returned != NULL) {
		retptr = returned;
		oriptr = original;
		while (1) {
			patloc = strstr(oriptr, pattern);
			if (!patloc)
				break;

			skplen = patloc - oriptr;
			strncpy(retptr, oriptr, skplen);
			retptr += skplen;

			strncpy(retptr, replacement, replen);
			retptr += replen;
			oriptr = patloc + patlen;
		}
		strcpy(retptr, oriptr);
	}
	return returned;
}

typedef struct url_ids_s {
	char		*tag;
	tmdb_fields_t	id;
} url_ids_t;

static url_ids_t ids_array[] = {
	{"movie_id",		MOVIE_ID},
	{"session_id",		SESSION_ID},
	{"collection_id",	COLLECTION_ID},
	{"person_id",		PERSON_ID},
	{"company_id",		COMPANY_ID},
	{"genre_id",		GENRE_ID},
};

static char *url_post_process(char *url, tmdb_request_ctx_t *ctx)
{
	int		i;
	char		*p1;
	char		*p2;
	char		*new_url = NULL;
	static char	tmp[4096];

	p1 = strstr(url, "{");

	if (!p1)
		return url;

	p2 = strstr(p1, "}");

	if (!p2)
		return url;

	strncpy(tmp, p1, (unsigned int)(p2 - p1 + 1));

	for (i = 0; i < (sizeof(ids_array) / sizeof(url_ids_t)); i++) {
		if (!strncmp(ids_array[i].tag, p1 + 1,
			MIN(strlen(ids_array[i].tag), strlen(tmp)))) {
			new_url = replace(url, tmp,
					  tmdb_ctx_get(ctx, ids_array[i].id));
		}
	}
	if (new_url) {
		free(url);
		url = new_url;
	}

	return url;
}

char *tmdb_get_url_from_ctx(tmdb_request_ctx_t *ctx)
{
	char	*url;
	int	i;
	int	f;

	if (!ctx)
		return NULL;
	if (!ctx->api_url)
		return NULL;
	if (!ctx->api_key)
		return NULL;

	url = malloc(TMDB_URL_MAX_LEN);
	memset(url, 0, TMDB_URL_MAX_LEN);

	/* URL */
	strcpy(url, tmdb_ctx_get(ctx, API_URL_F));

	/* METHOD */
	strcat(url, tmdb_method_type2str[ctx->request_type.type]);

	/* API KEY */
	strcat(url, tmdb_ctx_get(ctx, API_KEY_F));

	/* METHOD DATA */
	if (ctx->request_type.fields) {
		for (i = 0; i < 0x0F; i++) {
			f = 1 << i;
			if (ctx->request_type.fields & f) {
				if (field_str_get(f) != NULL) {
					strcat(url, field_str_get(f));
					strcat(url, tmdb_ctx_get(ctx, f));
				}
			}
		}
	}
	url = url_post_process(url, ctx);
#if 0
	printf("URL, %s\n", url);
#endif
	return url;
}

void init_data_chunk(net_data_t *data)
{
	tmdb_ctx_t *tmdb_ctx = NULL;

	tmdb_ctx = tmdb_get_ctx();

	if (!tmdb_ctx)
		return;

	if (!tmdb_ctx->net_init_data)
		return;

	tmdb_ctx->net_init_data(data);
}

void free_data_chunk(net_data_t *data)
{
	tmdb_ctx_t *tmdb_ctx = NULL;

	tmdb_ctx = tmdb_get_ctx();

	if (!tmdb_ctx)
		return;

	if (!tmdb_ctx->net_free_data)
		return;

	tmdb_ctx->net_free_data(data);
}

static void init_tok(jsmntok_t *tok, size_t tok_cnt)
{
	int i;

	if (!tok)
		return;
	memset(tok, 0, sizeof(jsmntok_t) * tok_cnt);

	for (i = 0; i < tok_cnt; i++)
		tok[i].type = -1;
}

int token_str_cmp(char *js, jsmntok_t *tok, const char *str)
{
	return strncmp(str, &js[tok[0].start], tok[0].end - tok[0].start);
}

void token_str_cpy(char *js, jsmntok_t *tok, char **str)
{
	*str = malloc(tok->end - tok->start + 1);
	memset(*str, 0, tok->end - tok->start + 1);
	strncpy(*str, &js[tok->start], tok->end - tok->start);
}

int print_token(char *js, jsmntok_t *tok)
{
	char *str;

	str = malloc(tok->end - tok->start + 1);
	memset(str, 0, tok->end - tok->start + 1);
	strncpy(str, &js[tok->start], tok->end - tok->start);
	printf("%s", str);
	free(str);

	return 0;
}

static void print_error_code(jsmntok_t *tok, size_t n_toks, char *js)
{
	int i = 0;

	if (tok[i++].type != JSMN_OBJECT)
		return;

	if (token_str_cmp(js, &tok[i++], "status_code"))
		return;

	printf("status_code:    ");
	print_token(js, &tok[i++]);
	printf("\n");

	if (token_str_cmp(js, &tok[i++], "status_message"))
		return;

	printf("status_message: ");
	print_token(js, &tok[i++]);
	printf("\n");
}

static void dump_data(jsmntok_t *tok, size_t n_toks, char *js)
{
	int i;

	for (i = 0; i < n_toks; i++) {
		printf("Type : ");
		switch (tok[i].type) {
		case JSMN_PRIMITIVE:
			printf("PRIMITIVE[%04d] (%d:%d)",
			       tok[i].size, i, tok[i].parent);
			print_token(js, &tok[i]);
			break;
		case JSMN_OBJECT:
			printf("OBJECT   [%04d] (%d:%d)",
			       tok[i].size, i, tok[i].parent);
			print_token(js, &tok[i]);
			break;
		case JSMN_ARRAY:
			printf("ARRAY    [%04d] (%d:%d)",
			       tok[i].size, i, tok[i].parent);
			print_token(js, &tok[i]);
			break;
		case JSMN_STRING:
			printf("STRING   [%04d] (%d:%d)",
			       tok[i].size, i, tok[i].parent);
			print_token(js, &tok[i]);
			break;
		default:
			printf("INVALID  [%04d] (%d:%d)",
			       tok[i].size, i, tok[i].parent);
			return;
		}
		printf("\n");
	}
}

int tag_copy(char	*js,
	     jsmntok_t	*tok,
	     jsmntype_t	type,
	     const char	*tag,
	     char	**dst)
{
	CHK((tok[0].type != JSMN_STRING), -1);
	CHK((token_str_cmp(js, &tok[0], tag)), -1);

	CHK((tok[1].type != type), -1);
	token_str_cpy(js, &tok[1], dst);

	return 0;
}

void header_process(net_data_t *data)
{
	char *status;
	int code = -1;

	if (!data) {
		data->err_code = -1;
		return;
	}
	if (!data->header.memory) {
		data->err_code = -1;
		return;
	}

	data->body_offset = data->header.size;

	status = strstr(data->header.memory, "Status: ");
	if (!status) {
		data->err_code = -1;
		return;
	}

	code = atoi(status + strlen("Status: "));

	if (code == 200)
		code = 0;
	data->err_code = code;
	return;
}

void body_process(net_data_t *data,
		  size_t num_tokens,
		  int (*cb)(jsmntok_t *tok, size_t cnt,
			    char *data, void *udata),
		  void *udata)
{
	int		result;
	int		dbg;
	jsmn_parser	json_parser;
	jsmntok_t	*tok;
	char		*js;

	if (!data)
		return;
	if (!data->body.memory)
		return;

	//printf("BODY: %s\n\n", data->body.memory);
	tok = malloc(sizeof(jsmntok_t) * num_tokens);
	init_tok(tok, num_tokens);

	jsmn_init(&json_parser);

	js = (char *)(data->body.memory + data->body_offset);

	result = jsmn_parse(&json_parser, js, tok, num_tokens);

	if (result == JSMN_SUCCESS) {
		if (data->err_code) {
			printf("HTTP error: %d\n\n", data->err_code);
			print_error_code(tok, num_tokens, js);
		} else {
			if (cb) {
				dbg = cb(tok, num_tokens, js, udata);
				if (dbg)
					dump_data(tok, num_tokens, js);
			} else
				dump_data(tok, num_tokens, js);
		}
	} else
		printf("Error parsing JSON: %d\n", result);
}

static char get_valid_symbol(char symbol)
{
	if ((symbol >= 'a') && (symbol <= 'z'))
		return symbol;
	
	if ((symbol >= 'A') && (symbol <= 'Z'))
		return symbol;
	
	if ((symbol >= '0') && (symbol <= '9'))
		return symbol;
	
	switch (symbol) {
		case '.':
		case '-':
		case '~':
		case '_':
			return symbol;
			break;
		default:
			return 0;
	}
	return 0;
}

char *escaped_string(const char * str)
{
	char	*data;
	char	symbol;
	char	n[4];
	char	*out = NULL;
	int	len;
	
	data = (char *)str;
	out = malloc(1);
	*out = 0;
	len = 1;
	
	while (*data) {
		symbol = get_valid_symbol(*data);
		if (symbol) {
			n[0] = symbol;
			n[1] = 0;
			len += 1;
		} else {
			sprintf(n, "%%%02x", *data);
			len += 3;
		}
		out = realloc(out, len);
		strcat(out, n);
		data++;
	}
	return out;
}

static tmdb_ctx_t *tmdb_ctx = NULL;

int tmdb_init(tmdb_ctx_t *ctx)
{
	if (!ctx)
		return -1;
	tmdb_ctx = ctx;

	return 0;
}

tmdb_ctx_t *tmdb_get_ctx(void)
{
	return tmdb_ctx;
}

int nethelper_get(const char *url_name,
		  const char *header_str,
		  net_data_t *data)
{
	int result = 0;
	tmdb_ctx_t *tmdb_ctx = NULL;

	tmdb_ctx = tmdb_get_ctx();

	if (!tmdb_ctx)
		result = -1;

	if (!result)
		if (!tmdb_ctx->net_get)
			result = -2;

	if (!result)
		result = tmdb_ctx->net_get(url_name, header_str, data);

	return result;
}
