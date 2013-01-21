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

#ifndef __PARSER_H_
#define __PARSER_H_

#include "jsmn.h"

#ifndef MIN
#define MIN(a, b) ({	__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a < _b ? _a : _b; })
#endif

#ifndef MAX
#define MAX(a, b) ({	__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a > _b ? _a : _b; })
#endif

#define TMDB_URL_MAX_LEN	8192

#define API_URL			"http://api.themoviedb.org/3/"

#define API_HEADER		"Accept: application/json"

#define TMDB_CONFIGURATION	"configuration"

#define TMDB_AUTH_TOKEN_NEW	"authentication/token/new"
#define TMDB_AUTH_SESSION_NEW	"authentication/session/new"

#define TMDB_ACOUNT		"acount"
#define TMDB_ACOUNT_FAV_MOVIES	"acount/{session_id}/favorite_movies"
#define TMDB_ACOUNT_FAV		"acount/{session_id}/favorite"
#define TMDB_ACOUNT_RATED	"acount/{session_id}/rated_movies"
#define TMDB_ACOUNT_WATCHLIST	"acount/{session_id}/movie_watchlist"

#define TMDB_MOVIE		"movie/{movie_id}"
#define TMDB_MOVIE_ALT_TITLES	"movie/{movie_id}/alternative_titles"
#define TMDB_MOVIE_CASTS	"movie/{movie_id}/casts"
#define TMDB_MOVIE_IMAGES	"movie/{movie_id}/images"
#define TMDB_MOVIE_KEYWORDS	"movie/{movie_id}/keywords"
#define TMDB_MOVIE_RELEASES	"movie/{movie_id}/releases"
#define TMDB_MOVIE_TRAILERS	"movie/{movie_id}/trailers"
#define TMDB_MOVIE_TRANSLATIONS	"movie/{movie_id}/translations"
#define TMDB_MOVIE_SIMILAR	"movie/{movie_id}/similar_movies"
#define TMDB_MOVIE_CHANGES	"movie/{movie_id}/changes"
#define TMDB_MOVIE_LATEST	"movie/latest"
#define TMDB_MOVIE_UPCOMING	"movie/upcoming"
#define TMDB_MOVIE_NOW_PLAYING	"movie/now_playing"
#define TMDB_MOVIE_POPULAR	"movie/popular"
#define TMDB_MOVIE_TOP_RATED	"movie/top_rated"
#define TMDB_MOVIE_RATING	"movie/{movie_id}/rating"

#define TMDB_COLLECTION		"collection/{collection_id}"
#define TMDB_COLLECTION_IMAGES	"collection/{collection_id}/images"

#define TMDB_PERSON		"person/{person_id}"
#define TMDB_PERSON_CREDITS	"person/{person_id}/credits"
#define TMDB_PERSON_IMAGES	"person/{person_id}/images"
#define TMDB_PERSON_CHANGES	"person/{person_id}/changes"
#define TMDB_PERSON_LATEST	"person/latest"

#define TMDB_COMPANY		"company/{company_id}"
#define TMDB_COMPANY_MOVIES	"company/{company_id}/movies"

#define TMDB_GENRE_LIST		"genre/list"
#define TMDB_GENRE_MOVIES	"genre/{genre_id}/movies"

#define TMDB_SEARCH_MOVIE	"search/movie"
#define TMDB_SEARCH_PERSON	"search/person"
#define TMDB_SEARCH_COMPANY	"search/company"

typedef enum tmdb_method_type_e {
	CONFIGURATION,

	AUTH_TOKEN_NEW,
	AUTH_SESSION_NEW,

	ACOUNT,
	ACOUNT_FAV_MOVIES,
	ACOUNT_FAV,
	ACOUNT_RATED,
	ACOUNT_WATCHLIST,

	MOVIE,
	MOVIE_ALT_TITLES,
	MOVIE_CASTS,
	MOVIE_IMAGES,
	MOVIE_KEYWORDS,
	MOVIE_RELEASES,
	MOVIE_TRAILERS,
	MOVIE_TRANSLATIONS,
	MOVIE_SIMILAR,
	MOVIE_CHANGES,
	MOVIE_LATEST,
	MOVIE_UPCOMING,
	MOVIE_NOW_PLAYING,
	MOVIE_POPULAR,
	MOVIE_TOP_RATED,
	MOVIE_RATING,

	COLLECTION,
	COLLECTION_IMAGES,

	PERSON,
	PERSON_CREDITS,
	PERSON_IMAGES,
	PERSON_CHANGES,
	PERSON_LATEST,

	COMPANY,
	COMPANY_MOVIES,

	GENRE_LIST,
	GENRE_MOVIES,

	SEARCH_MOVIE,
	SEARCH_PERSON,
	SEARCH_COMPANY,
} tmdb_method_type_t;

typedef enum tmdb_fields_e {
	NONE			= 0 << 0x00,
	PAGE			= 1 << 0x00,
	QUERY			= 1 << 0x01,
	LANGUAGE		= 1 << 0x02,
	INCLUDE_ADULT		= 1 << 0x03,
	REQUEST_TOKEN		= 1 << 0x04,
	FAVORITE		= 1 << 0x05,
	MOVIE_WATCHLIST		= 1 << 0x06,
	COUNTRY			= 1 << 0x07,
	VALUE			= 1 << 0x08,
	YEAR			= 1 << 0x09,
	START_DATE		= 1 << 0x0A,
	END_DATE		= 1 << 0x0B,
	APPEND_TO_RESPONSE	= 1 << 0x0C,

	SESSION_ID		= 1 << 0x0D,
	MOVIE_ID		= 1 << 0x0E,
	GENRE_ID		= 1 << 0x0F,
	COLLECTION_ID		= 1 << 0x10,
	PERSON_ID		= 1 << 0x11,
	COMPANY_ID		= 1 << 0x12,

	API_URL_F		= 1 << 0x13,
	API_HEADER_F		= 1 << 0x14,
	API_KEY_F		= 1 << 0x15,
} tmdb_fields_t;

typedef struct tmdb_method_s {
	tmdb_method_type_t	type;
	tmdb_fields_t		fields;
} tmdb_method_t;

typedef struct tmdb_request_ctx_s {
	tmdb_method_t	request_type;
	char		*api_header;
	char		*api_url;
	char		*api_key;
	char		*page;
	char		*query;
	char		*language;
	char		*include_adult;
	char		*request_token;
	char		*session_id;
	char		*movie_id;
	char		*favorite;
	char		*movie_watchlist;
	char		*append_to_response;
	char		*country;
	char		*value;
	char		*year;
	char		*start_date;
	char		*end_date;
	char		*genre_id;
	char		*collection_id;
	char		*person_id;
	char		*company_id;
} tmdb_request_ctx_t;

#define TOKEN_STRING(js, t, s)					\
	(strncmp(js+(t).start, s, (t).end - (t).start) == 0	\
	&& strlen(s) == (t).end - (t).start)

#define CPTAGT(__type, __tag, __dst)  { \
		CHK(tag_copy(data, &tok[i], __type, __tag, __dst), -1); \
		i += 2; \
	}

#define CPTAG(__type, __tag, __dst)  { \
		tag_copy(data, &tok[i], __type, __tag, __dst); \
		i += 2; \
	}

int tmdb_ctx_set(tmdb_request_ctx_t	*ctx,
		 tmdb_fields_t		field,
		 const char		*data);

char *tmdb_ctx_get(tmdb_request_ctx_t	*ctx,
		   tmdb_fields_t	field);

void free_ctx(tmdb_request_ctx_t *ctx);

void init_data_chunk(net_data_t *data);

void free_data_chunk(net_data_t *data);

void header_process(net_data_t *data);

void body_process(net_data_t	*data,
		  size_t	num_tokens,
		  int (*cb)(jsmntok_t	*tok,
			    size_t	cnt,
			    char	*data,
			    void	*udata),
		  void		*udata);

char *tmdb_get_url_from_ctx(tmdb_request_ctx_t *ctx);

int print_token(char		*js,
		jsmntok_t	*tok);

void token_str_cpy(char		*js,
		   jsmntok_t	*tok,
		   char		**str);

int token_str_cmp(char		*js,
		  jsmntok_t	*tok,
		  const char	*str);

int tag_copy(char		*js,
	     jsmntok_t		*tok,
	     jsmntype_t		type,
	     const char		*tag,
	     char		**dst);

char *escaped_string(const char * str);

tmdb_ctx_t *tmdb_get_ctx(void);

int nethelper_get(const char *url_name,
		  const char *header_str,
		  net_data_t *data);

#endif
