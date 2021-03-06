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

#include "genre_movies.h"

static int genre_movies_parse(jsmntok_t	*tok,
			    size_t	cnt,
			    char	*data,
			    void	*udata)
{
	int i = 0;
	tmdb_movie_t **movie = (tmdb_movie_t **)udata;
	tmdb_movie_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);
	CHK((tok[i].type != JSMN_STRING), -1);
	CHK(token_str_cmp(data, &tok[i++], "id"), -1);
	CHK((tok[i++].type != JSMN_PRIMITIVE), -1);
	CHK(token_str_cmp(data, &tok[i++], "page"), -1);
	CHK((tok[i++].type != JSMN_PRIMITIVE), -1);
	CHK(token_str_cmp(data, &tok[i++], "results"), -1);

	if (tok[i].type == JSMN_ARRAY) {
		count = tok[i].size;
		i++;
	}

	CHK(!count, -1);

	for (; count--;) {
		*movie = malloc(sizeof(tmdb_movie_t));
		info = *movie;
		memset(info, 0, sizeof(tmdb_movie_t));
		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAG(JSMN_STRING,     "backdrop_path",  &info->backdrop_path);
		CPTAGT(JSMN_PRIMITIVE, "id",             &info->id);
		CPTAGT(JSMN_STRING,    "original_title", &info->original_title);
		CPTAG(JSMN_STRING,     "release_date",   &info->release_date);
		CPTAG(JSMN_STRING,     "poster_path",    &info->poster_path);
		CPTAG(JSMN_STRING,     "title",          &info->title);
		CPTAG(JSMN_PRIMITIVE,  "vote_average",   &info->vote_average);
		CPTAG(JSMN_PRIMITIVE,  "vote_count",     &info->vote_count);
		movie = &info->next;
	}
	return 0;
}

/*
	GENRE / MOVIES
*/
tmdb_movie_t *tmdb_genre_movies(const char *genre_id,
				const char *language,
				const char *page)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_t		*movies = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = GENRE_MOVIES;
	if (genre_id)
		tmdb_ctx_set(&ctx, GENRE_ID, genre_id);
	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);
	if (page)
		tmdb_ctx_set(&ctx, PAGE, page);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, GENRE_MOVIES_NUM_TOKENS,
			     genre_movies_parse, &movies);
	}
	free_data_chunk(&data);

	return movies;
}
