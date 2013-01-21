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

#include "movie_trailers.h"

static int movie_trailers_parse(jsmntok_t	*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_movie_trailers_t **movie_trailers =
				(tmdb_movie_trailers_t **)udata;
	tmdb_trailer_t	   **qt_trailers;
	tmdb_trailer_t	   *qt_trailer;
	tmdb_trailer_t	   **youtube_trailers;
	tmdb_trailer_t	   *youtube_trailer;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*movie_trailers = malloc(sizeof(tmdb_movie_trailers_t));
	memset(*movie_trailers, 0, sizeof(tmdb_movie_trailers_t));

	CPTAGT(JSMN_PRIMITIVE, "id", &((*movie_trailers)->id));

	CHK((token_str_cmp(data, &tok[i++], "quicktime")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	qt_trailers = &((*movie_trailers)->quicktime);
	for (; count--;) {
		*qt_trailers = malloc(sizeof(tmdb_trailer_t));
		qt_trailer = *qt_trailers;
		memset(qt_trailer, 0, sizeof(tmdb_trailer_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING, "name",   &qt_trailer->name);
		CPTAGT(JSMN_STRING, "size",   &qt_trailer->size);
		CPTAGT(JSMN_STRING, "source", &qt_trailer->source);

		qt_trailers = &qt_trailer->next;
	}

	CHK((token_str_cmp(data, &tok[i++], "youtube")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	youtube_trailers = &((*movie_trailers)->youtube);
	for (; count--;) {
		*youtube_trailers = malloc(sizeof(tmdb_trailer_t));
		youtube_trailer = *youtube_trailers;
		memset(youtube_trailer, 0, sizeof(tmdb_trailer_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING, "name",   &youtube_trailer->name);
		CPTAGT(JSMN_STRING, "size",   &youtube_trailer->size);
		CPTAGT(JSMN_STRING, "source", &youtube_trailer->source);

		youtube_trailers = &youtube_trailer->next;
	}

	return 0;
}
/*
	MOVIE / GET_TRAILERS
*/
tmdb_movie_trailers_t *tmdb_movie_trailers(const char *movie_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_trailers_t	*movie_trailers = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_TRAILERS;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_TRAILERS_NUM_TOKENS,
			     movie_trailers_parse, &movie_trailers);
	}
	free_data_chunk(&data);

	return movie_trailers;
}
