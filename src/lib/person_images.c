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

#include "person_images.h"

static int person_images_parse(jsmntok_t	*tok,
			       size_t		cnt,
			       char		*data,
			       void		*udata)
{
	int i = 0;
	tmdb_image_t **images = (tmdb_image_t **)udata;
	tmdb_image_t *info;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "id")), -1);
	i++;
	CHK((token_str_cmp(data, &tok[i++], "profiles")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;

	for (; count--;) {
		*images = malloc(sizeof(tmdb_image_t));
		info = *images;
		memset(info, 0, sizeof(tmdb_image_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING,    "file_path",    &info->file_path);
		CPTAGT(JSMN_PRIMITIVE, "width",        &info->width);
		CPTAGT(JSMN_PRIMITIVE, "height",       &info->height);
		CPTAG(JSMN_PRIMITIVE,  "iso_639_1",    &info->iso_639_1);
		CPTAG(JSMN_PRIMITIVE,  "aspect_ratio", &info->aspect_ratio);

		images = &info->next;
	}

	return 0;
}

/*
	PERSON / IMAGES
*/
tmdb_image_t *tmdb_person_images(const char *person_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_image_t		*person_images = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = PERSON_IMAGES;
	tmdb_ctx_set(&ctx, PERSON_ID, person_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, PERSON_IMAGES_NUM_TOKENS,
			     person_images_parse, &person_images);
	}
	free_data_chunk(&data);

	return person_images;
}
