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

#include "movie_images.h"

static int movie_images_parse(jsmntok_t *tok,
			      size_t cnt,
			      char *data,
			      void *udata)
{
	int i = 0;
	tmdb_movie_images_t **movie_images = (tmdb_movie_images_t **)udata;
	tmdb_image_t	   **backdrops;
	tmdb_image_t	   *backdrop;
	tmdb_image_t	   **posters;
	tmdb_image_t	   *poster;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*movie_images = malloc(sizeof(tmdb_movie_images_t));
	memset(*movie_images, 0, sizeof(tmdb_movie_images_t));

	CPTAGT(JSMN_PRIMITIVE, "id", &((*movie_images)->id));

	CHK((token_str_cmp(data, &tok[i++], "backdrops")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	backdrops = &((*movie_images)->backdrops);
	for (; count--;) {
		*backdrops = malloc(sizeof(tmdb_image_t));
		backdrop = *backdrops;
		memset(backdrop, 0, sizeof(tmdb_image_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING,    "file_path",    &backdrop->file_path);
		CPTAGT(JSMN_PRIMITIVE, "width",        &backdrop->width);
		CPTAGT(JSMN_PRIMITIVE, "height",       &backdrop->height);
		CPTAG(JSMN_STRING,     "iso_639_1",    &backdrop->iso_639_1);
		CPTAGT(JSMN_PRIMITIVE, "aspect_ratio", &backdrop->aspect_ratio);
		CPTAG(JSMN_PRIMITIVE,  "vote_average", &backdrop->vote_average);
		CPTAG(JSMN_PRIMITIVE,  "vote_count",   &backdrop->vote_count);
		backdrops = &backdrop->next;
	}

	CHK((token_str_cmp(data, &tok[i++], "posters")), -1);

	posters = &((*movie_images)->posters);
	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*posters = malloc(sizeof(tmdb_image_t));
		poster = *posters;
		memset(poster, 0, sizeof(tmdb_image_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING,    "file_path",    &poster->file_path);
		CPTAGT(JSMN_PRIMITIVE, "width",        &poster->width);
		CPTAGT(JSMN_PRIMITIVE, "height",       &poster->height);
		CPTAG(JSMN_STRING,     "iso_639_1",    &poster->iso_639_1);
		CPTAGT(JSMN_PRIMITIVE, "aspect_ratio", &poster->aspect_ratio);
		CPTAG(JSMN_PRIMITIVE,  "vote_average", &poster->vote_average);
		CPTAG(JSMN_PRIMITIVE,  "vote_count",   &poster->vote_count);
		posters = &poster->next;
	}

	return 0;
}
/*
	MOVIE / GET_IMAGES
*/
tmdb_movie_images_t *tmdb_movie_images(const char *movie_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_images_t	*movie_images = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_IMAGES;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_IMAGES_NUM_TOKENS,
			     movie_images_parse, &movie_images);
	}
	free_data_chunk(&data);

	return movie_images;
}
