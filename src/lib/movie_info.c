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

#include "movie_info.h"

static int parse_genres(jsmntok_t *tok, char *data, tmdb_genre_t **genres_p)
{
	int		i = 0;
	int		count;
	tmdb_genre_t	*genre;
	tmdb_genre_t	**genres;

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "genres")), -1);

	CHK((tok[i].type != JSMN_ARRAY), -1);
	count = tok[i++].size;

	genres = genres_p;

	for (; count--;) {
		*genres = malloc(sizeof(tmdb_genre_t));
		genre = *genres;
		memset(genre, 0, sizeof(tmdb_genre_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAG(JSMN_PRIMITIVE, "id", &genre->id);
		CPTAG(JSMN_STRING, "name", &genre->name);

		genres = &genre->next;
	}

	return i;
}

static int parse_production_companies(jsmntok_t		*tok,
				      char		*data,
				      tmdb_company_t	**companies_p)
{
	int		i = 0;
	int		count;
	tmdb_company_t	*company;
	tmdb_company_t	**companies;

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "production_companies")), -1);

	CHK((tok[i].type != JSMN_ARRAY), -1);
	count = tok[i++].size;
	companies = companies_p;

	for (; count--;) {
		*companies = malloc(sizeof(tmdb_company_t));
		company = *companies;
		memset(company, 0, sizeof(tmdb_company_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAGT(JSMN_STRING, "name", &company->id);
		CPTAG(JSMN_PRIMITIVE,     "id",  &company->name);

		companies = &company->next;
	}

	return i;
}

static int parse_production_countries(jsmntok_t		*tok,
				      char		*data,
				      tmdb_country_t	**countries_p)
{
	int		i = 0;
	int		count;
	tmdb_country_t **countries;
	tmdb_country_t *country;

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "production_countries")), -1);

	CHK((tok[i].type != JSMN_ARRAY), -1);
	count = tok[i++].size;
	countries = countries_p;

	for (; count--;) {
		*countries = malloc(sizeof(tmdb_country_t));
		country = *countries;
		memset(country, 0, sizeof(tmdb_country_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAG(JSMN_STRING, "iso_3166_1", &country->iso_3166_1);
		CPTAG(JSMN_STRING, "name",       &country->name);

		countries = &country->next;
	}

	return i;
}

static int parse_spoken_languages(jsmntok_t		*tok,
				  char			*data,
				  tmdb_language_t	**languages_p)
{
	int		i = 0;
	int		count;
	tmdb_language_t	*language;
	tmdb_language_t	**languages;

	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "spoken_languages")), -1);

	CHK((tok[i].type != JSMN_ARRAY), -1);
	count = tok[i++].size;

	languages = languages_p;

	for (; count--;) {
		*languages = malloc(sizeof(tmdb_language_t));
		language = *languages;
		memset(language, 0, sizeof(tmdb_language_t));

		CHK((tok[i++].type != JSMN_OBJECT), -1);
		CPTAG(JSMN_STRING, "iso_639_1", &language->iso_639_1);
		CPTAG(JSMN_STRING, "name",      &language->name);

		languages = &language->next;
	}

	return i;
}

static int movie_info_parse(jsmntok_t *tok, size_t cnt, char *data, void *udata)
{
	int		i = 0;
	tmdb_movie_t	**info_p = (tmdb_movie_t **)udata;
	tmdb_movie_t	*info;

	CHK((tok[i++].type != JSMN_OBJECT), -1);

	*info_p = malloc(sizeof(tmdb_movie_t));
	info = *info_p;
	memset(info, 0, sizeof(tmdb_movie_t));
	CPTAG(JSMN_PRIMITIVE, "adult",         &info->adult);
	CPTAG(JSMN_STRING,    "backdrop_path", &info->backdrop_path);

	/* belongs_to_collection */
	CHK((tok[i].type != JSMN_STRING), -1);
	CHK((token_str_cmp(data, &tok[i++], "belongs_to_collection")), -1);
	if (tok[i].type == JSMN_OBJECT) {
		/* skip for now */
		/*token_str_cmp(data, &tok[i++], "null") */
#if 0
		printf("skip %d\n", tok[i].size);
#endif
		CHK((tok[i].type != JSMN_OBJECT), -1);
		i += tok[i].size;
	}
	i++;

	CPTAG(JSMN_PRIMITIVE, "budget",         &info->budget);

	i += parse_genres(&tok[i], data, &info->genres);

	CPTAG(JSMN_STRING,    "homepage",       &info->home_page);
	CPTAG(JSMN_PRIMITIVE, "id",             &info->id);
	CPTAG(JSMN_STRING,    "imdb_id",        &info->imdb_id);
	CPTAG(JSMN_STRING,    "original_title", &info->original_title);
	CPTAG(JSMN_STRING,    "overview",       &info->overview);
	CPTAG(JSMN_PRIMITIVE, "popularity",     &info->popularity);
	CPTAG(JSMN_STRING,    "poster_path",    &info->poster_path);
	/*production_companies*/
	i += parse_production_companies(&tok[i],
					data, &info->production_companies);
	/*production_countries*/
	i += parse_production_countries(&tok[i],
					data, &info->production_countries);

	CPTAG(JSMN_STRING,    "release_date",  &info->release_date);
	CPTAG(JSMN_PRIMITIVE, "revenue",       &info->revenue);
	CPTAG(JSMN_PRIMITIVE, "runtime",       &info->runtime);

	/*spoken_languages*/
	i += parse_spoken_languages(&tok[i], data, &info->spoken_languages);

	CPTAG(JSMN_STRING,    "status",        &info->status);
	CPTAG(JSMN_STRING,    "tagline",       &info->tagline);
	CPTAG(JSMN_STRING,    "title",         &info->title);
	CPTAG(JSMN_PRIMITIVE, "vote_average",  &info->vote_average);
	CPTAG(JSMN_PRIMITIVE, "vote_count",    &info->vote_count);

	return 0;
}

/*
	MOVIE / GET BASIC INFO
*/
tmdb_movie_t *tmdb_movie_info(const char	*movie_id,
				    const char  *language)
{
	int			result;
	char			*url_str;
	net_data_t		data;
	tmdb_request_ctx_t	ctx;
	tmdb_movie_t		*info = NULL;

	init_data_chunk(&data);

	memset(&ctx, 0, sizeof(tmdb_request_ctx_t));
	tmdb_ctx_set(&ctx, API_URL_F, NULL);
	tmdb_ctx_set(&ctx, API_HEADER_F, NULL);
	tmdb_ctx_set(&ctx, API_KEY_F, NULL);
	ctx.request_type.type = MOVIE;
	tmdb_ctx_set(&ctx, MOVIE_ID, movie_id);
	if (language)
		tmdb_ctx_set(&ctx, LANGUAGE, language);

	url_str = tmdb_get_url_from_ctx(&ctx);

	result = nethelper_get(url_str, API_HEADER, &data);

	free(url_str);
	free_ctx(&ctx);

	if (!result) {
		header_process(&data);
		body_process(&data, MOVIE_INFO_NUM_TOKENS,
			     movie_info_parse, &info);
	}
	free_data_chunk(&data);

	return info;
}
