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

#include "search_movie.h"

static int movie_search_parse(jsmntok_t		*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_movie_t **movie = (tmdb_movie_t **)udata;
	tmdb_movie_t *info;
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
		*movie = malloc(sizeof(tmdb_movie_t));
		info = *movie;
		memset(info, 0, sizeof(tmdb_movie_t));
		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_PRIMITIVE, "adult", &info->adult);
		CPTAG(JSMN_STRING,     "backdrop_path", &info->backdrop_path);
		CPTAGT(JSMN_PRIMITIVE, "id", &info->id);
		CPTAGT(JSMN_STRING,    "original_title", &info->original_title);
		CPTAG(JSMN_STRING,     "release_date", &info->release_date);
		CPTAG(JSMN_STRING,     "poster_path", &info->poster_path);
		CPTAG(JSMN_PRIMITIVE,  "popularity", &info->popularity);
		CPTAG(JSMN_STRING,     "title", &info->title);
		CPTAG(JSMN_PRIMITIVE,  "vote_average", &info->vote_average);
		CPTAG(JSMN_PRIMITIVE,  "vote_count", &info->vote_count);
		movie = &info->next;
	}

	return 0;
}

/*
	SEARCH / MOVIE
*/

tmdb_movie_t *tmdb_search_movie(const char	*name,
				const char	*language,
				int		adult,
				const char	*year)
{
	int			result;
	char			*url_str;
	char			*esc_name;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_t		*movies = NULL;

	init_data_chunk(&data);

	esc_name = escaped_string(name);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = SEARCH_MOVIE;
	tmdb_ctx_set(&ctx, QUERY, esc_name);

	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);

	if (adult)
		tmdb_ctx_set(&ctx, INCLUDE_ADULT, "true");

	if (year)
		tmdb_ctx_set(&ctx, YEAR, year);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);
	free(esc_name);

	if (!result) {
		header_process(&data);
		body_process(&data, SEARCH_MOVIE_NUM_TOKENS,
			     movie_search_parse, &movies);
	}
	free_data_chunk(&data);

	return movies;
}
