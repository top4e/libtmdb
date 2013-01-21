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

#include "movie_releases.h"

static int movie_releases_parse(jsmntok_t	*tok,
				size_t		cnt,
				char		*data,
				void		*udata)
{
	int i = 0;
	tmdb_movie_releases_t **movie_releases =
				(tmdb_movie_releases_t **)udata;
	tmdb_release_t	   **releases;
	tmdb_release_t	   *release;
	int count = 0;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*movie_releases = malloc(sizeof(tmdb_movie_releases_t));
	memset(*movie_releases, 0, sizeof(tmdb_movie_releases_t));

	CPTAGT(JSMN_PRIMITIVE, "id", &((*movie_releases)->id));

	CHK((token_str_cmp(data, &tok[i++], "countries")), -1);

	if (tok[i].type == JSMN_ARRAY)
		count = tok[i++].size;
	releases = &((*movie_releases)->releases);
	for (; count--;) {
		*releases = malloc(sizeof(tmdb_release_t));
		release = *releases;
		memset(release, 0, sizeof(tmdb_release_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING, "iso_3166_1",    &release->iso_3166_1);
		CPTAGT(JSMN_STRING, "certification", &release->certification);
		CPTAGT(JSMN_STRING, "release_date",  &release->release_date);

		releases = &release->next;
	}

	return 0;
}
/*
	MOVIE / GET_RELEASES
*/
tmdb_movie_releases_t *tmdb_movie_releases(const char *movie_id)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_releases_t	*movie_releases = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE_RELEASES;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_RELEASES_NUM_TOKENS,
			     movie_releases_parse, &movie_releases);
	}
	free_data_chunk(&data);

	return movie_releases;
}
