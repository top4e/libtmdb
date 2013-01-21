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

#include "movie_similar.h"

static int movie_similar_parse(jsmntok_t	*tok,
			       size_t		cnt,
			       char		*data,
			       void		*udata)
{
	int i = 0;
	tmdb_movie_t **movies = (tmdb_movie_t **)udata;
	tmdb_movie_t *movie;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((token_str_cmp(data, &tok[i++], "page")), -1);
	i++;
	CHK((token_str_cmp(data, &tok[i++], "results")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*movies = malloc(sizeof(tmdb_movie_t));
		movie = *movies;
		memset(movie, 0, sizeof(tmdb_movie_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAG(JSMN_STRING,     "backdrop_path",
		      &movie->backdrop_path);
		CPTAGT(JSMN_PRIMITIVE, "id",
		       &movie->id);
		CPTAGT(JSMN_STRING,    "original_title",
		       &movie->original_title);
		CPTAGT(JSMN_STRING,    "release_date",
		       &movie->release_date);
		CPTAG(JSMN_STRING,     "poster_path",
		      &movie->poster_path);
		CPTAGT(JSMN_STRING,    "title",
		       &movie->title);
		CPTAGT(JSMN_PRIMITIVE, "vote_average",
		       &movie->vote_average);
		CPTAGT(JSMN_PRIMITIVE, "vote_count",
		       &movie->vote_count);

		movies = &movie->next;
	}

	return 0;
}

/*
	MOVIE / GET SIMILAR MOVIES
*/
tmdb_movie_t *tmdb_movie_similar(const char *movie_id, const char *language)
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
	ctx.request_type.type = MOVIE_SIMILAR;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);
	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_SIMILAR_NUM_TOKENS,
			     movie_similar_parse, &movies);
	}
	free_data_chunk(&data);

	return movies;
}
