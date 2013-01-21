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

#include "data.h"

#include "tmdb.h"

void tmdb_clean_configuration(tmdb_configuration_t *configuration)
{
	int i;

	if (!configuration)
		return;

	if (configuration->base_url)
		free(configuration->base_url);

	if (configuration->secure_base_url)
		free(configuration->secure_base_url);

	if (configuration->poster_sizes) {
		for (i = 0; i < configuration->poster_sizes_cnt; i++) {
			if (configuration->poster_sizes[i])
				free(configuration->poster_sizes[i]);
		}
	}

	if (configuration->backdrop_sizes) {
		for (i = 0; i < configuration->backdrop_sizes_cnt; i++) {
			if (configuration->backdrop_sizes[i])
				free(configuration->backdrop_sizes[i]);
		}
	}

	if (configuration->profile_sizes) {
		for (i = 0; i < configuration->profile_sizes_cnt; i++) {
			if (configuration->profile_sizes[i])
				free(configuration->profile_sizes[i]);
		}
	}

	if (configuration->logo_sizes) {
		for (i = 0; i < configuration->logo_sizes_cnt; i++) {
			if (configuration->logo_sizes[i])
				free(configuration->logo_sizes[i]);
		}
	}
	free(configuration);
}

void tmdb_clean_person_type(tmdb_person_t *person)
{
	tmdb_person_t *person_p = person;
	int i;

	while (person_p) {
		if (person_p->adult)
			free(person_p->adult);
		if (person_p->biography)
			free(person_p->biography);
		if (person_p->birthday)
			free(person_p->birthday);
		if (person_p->deathday)
			free(person_p->deathday);
		if (person_p->homepage)
			free(person_p->homepage);
		if (person_p->id)
			free(person_p->id);
		if (person_p->name)
			free(person_p->name);
		if (person_p->place_of_birth)
			free(person_p->place_of_birth);
		if (person_p->profile_path)
			free(person_p->profile_path);

		if (person_p->also_known_as) {
			for (i = 0; i < person_p->aka_cnt; i++) {
				if (person_p->also_known_as[i])
					free(person_p->also_known_as[i]);
			}
		}
		person_p = person_p->next;
	}

	if (person)
		free(person);
}

static void clean_company(tmdb_company_t *company)
{
	if (!company)
		return;

	if (company->description)
		free(company->description);
	if (company->headquarters)
		free(company->headquarters);
	if (company->homepage)
		free(company->homepage);
	if (company->id)
		free(company->id);
	if (company->name)
		free(company->name);
	if (company->logo_path)
		free(company->logo_path);
}

void tmdb_clean_company_type(tmdb_company_t *company)
{
	tmdb_company_t *company_p = company;

	while (company_p) {
		clean_company(company_p);
		clean_company(company_p->parent_company);
		company_p = company_p->next;
	}

	free(company);
}

void tmdb_clean_auth_token_type(auth_token_t *auth_token)
{
	if (!auth_token)
		return;

	if (auth_token->expires_at)
		free(auth_token->expires_at);

	if (auth_token->token)
		free(auth_token->token);

	free(auth_token);
}

void tmdb_clean_genre_type(tmdb_genre_t *genre_list)
{
	tmdb_genre_t *genre_list_p = genre_list;

	while (genre_list_p) {
		if (genre_list_p->id)
			free(genre_list_p->id);
		if (genre_list_p->name)
			free(genre_list_p->name);

		genre_list_p = genre_list_p->next;
	}

	if (genre_list)
		free(genre_list);
}

void tmdb_clean_cast_type(tmdb_cast_t *cast)
{
	tmdb_cast_t *cast_p = cast;

	while (cast_p) {
		if (cast_p->id)
			free(cast_p->id);
		if (cast_p->name)
			free(cast_p->name);
		if (cast_p->character)
			free(cast_p->character);
		if (cast_p->order)
			free(cast_p->order);
		if (cast_p->cast_id)
			free(cast_p->cast_id);
		if (cast_p->profile_path)
			free(cast_p->profile_path);

		cast_p = cast_p->next;
	}

	if (cast)
		free(cast);
}

void tmdb_clean_crew_type(tmdb_crew_t *crew)
{
	tmdb_crew_t *crew_p = crew;

	while (crew_p) {
		if (crew_p->id)
			free(crew_p->id);
		if (crew_p->name)
			free(crew_p->name);
		if (crew_p->department)
			free(crew_p->department);
		if (crew_p->job)
			free(crew_p->job);
		if (crew_p->profile_path)
			free(crew_p->profile_path);

		crew_p = crew_p->next;
	}

	if (crew)
		free(crew);
}

void tmdb_clean_movie_casts_type(tmdb_movie_casts_t *movie_casts)
{
	tmdb_movie_casts_t *movie_casts_p = movie_casts;

	while (movie_casts_p) {
		if (movie_casts_p->id)
			free(movie_casts_p->id);
		tmdb_clean_cast_type(movie_casts_p->cast);
		tmdb_clean_crew_type(movie_casts_p->crew);
		movie_casts_p = movie_casts_p->next;
	}

	if (movie_casts)
		free(movie_casts);
}

void tmdb_clean_image_type(tmdb_image_t *image)
{
	tmdb_image_t *image_p = image;

	while (image_p) {
		if (image_p->file_path)
			free(image_p->file_path);
		if (image_p->width)
			free(image_p->width);
		if (image_p->height)
			free(image_p->height);
		if (image_p->iso_639_1)
			free(image_p->iso_639_1);
		if (image_p->aspect_ratio)
			free(image_p->aspect_ratio);
		if (image_p->vote_average)
			free(image_p->vote_average);
		if (image_p->vote_count)
			free(image_p->vote_count);

		image_p = image_p->next;
	}

	if (image)
		free(image);
}

void tmdb_clean_person_credits_type(tmdb_person_credits_t *person_credits)
{
	tmdb_person_credits_t *person_credits_p = person_credits;

	while (person_credits_p) {
		if (person_credits_p->character)
			free(person_credits_p->character);
		tmdb_clean_movie_type(person_credits_p->movie);

		person_credits_p = person_credits_p->next;
	}

	if (person_credits)
		free(person_credits);
}

void tmdb_clean_release_type(tmdb_release_t *release)
{
	tmdb_release_t *release_p = release;

	while (release_p) {
		if (release_p->iso_3166_1)
			free(release_p->iso_3166_1);
		if (release_p->certification)
			free(release_p->certification);
		if (release_p->release_date)
			free(release_p->release_date);

		release_p = release_p->next;
	}

	if (release)
		free(release);
}

void tmdb_clean_movie_images_type(tmdb_movie_images_t *movie_images)
{
	tmdb_movie_images_t *movie_images_p = movie_images;

	while (movie_images_p) {
		if (movie_images_p->id)
			free(movie_images_p->id);
		tmdb_clean_image_type(movie_images_p->backdrops);
		tmdb_clean_image_type(movie_images_p->posters);

		movie_images_p = movie_images_p->next;
	}

	if (movie_images)
		free(movie_images);
}

void tmdb_clean_keywords_type(tmdb_keywords_t *keywords)
{
	tmdb_keywords_t *keywords_p = keywords;

	while (keywords_p) {
		if (keywords_p->id)
			free(keywords_p->id);
		if (keywords_p->name)
			free(keywords_p->name);

		keywords_p = keywords_p->next;
	}

	if (keywords)
		free(keywords);
}

void tmdb_clean_movie_keywords_type(tmdb_movie_keywords_t *movie_keywords)
{
	tmdb_movie_keywords_t *movie_keywords_p = movie_keywords;

	while (movie_keywords_p) {
		if (movie_keywords_p->id)
			free(movie_keywords_p->id);
		tmdb_clean_keywords_type(movie_keywords_p->keywords);

		movie_keywords_p = movie_keywords_p->next;
	}

	if (movie_keywords)
		free(movie_keywords);
}

void tmdb_clean_movie_releases_type(tmdb_movie_releases_t *movie_releases)
{
	tmdb_movie_releases_t *movie_releases_p = movie_releases;

	while (movie_releases_p) {
		if (movie_releases_p->id)
			free(movie_releases_p->id);
		tmdb_clean_release_type(movie_releases_p->releases);

		movie_releases_p = movie_releases_p->next;
	}

	if (movie_releases)
		free(movie_releases);
}

void tmdb_clean_trailer_type(tmdb_trailer_t *trailer)
{
	tmdb_trailer_t *trailer_p = trailer;

	while (trailer_p) {
		if (trailer_p->name)
			free(trailer_p->name);
		if (trailer_p->size)
			free(trailer_p->size);
		if (trailer_p->source)
			free(trailer_p->source);

		trailer_p = trailer_p->next;
	}

	if (trailer)
		free(trailer);
}

void tmdb_clean_movie_trailers_type(tmdb_movie_trailers_t *movie_trailers)
{
	tmdb_movie_trailers_t *movie_trailers_p = movie_trailers;

	while (movie_trailers_p) {
		if (movie_trailers_p->id)
			free(movie_trailers_p->id);
		tmdb_clean_trailer_type(movie_trailers_p->quicktime);
		tmdb_clean_trailer_type(movie_trailers_p->youtube);

		movie_trailers_p = movie_trailers_p->next;
	}

	if (movie_trailers)
		free(movie_trailers);
}

void tmdb_clean_translation_type(tmdb_translation_t *translation)
{
	tmdb_translation_t *translation_p = translation;

	while (translation_p) {
		if (translation_p->iso_639_1)
			free(translation_p->iso_639_1);
		if (translation_p->name)
			free(translation_p->name);
		if (translation_p->english_name)
			free(translation_p->english_name);

		translation_p = translation_p->next;
	}

	if (translation)
		free(translation);
}

void tmdb_clean_movie_translations_type(
				tmdb_movie_translations_t *movie_translations)
{
	tmdb_movie_translations_t *movie_translations_p = movie_translations;

	while (movie_translations_p) {
		if (movie_translations_p->id)
			free(movie_translations_p->id);
		tmdb_clean_translation_type(movie_translations_p->translations);

		movie_translations_p = movie_translations_p->next;
	}

	if (movie_translations)
		free(movie_translations);
}

void tmdb_clean_collection_type(tmdb_collection_t *collection)
{
	tmdb_collection_t *collection_p = collection;

	while (collection_p) {
		if (collection_p->backdrop_path)
			free(collection_p->backdrop_path);
		if (collection_p->id)
			free(collection_p->id);
		if (collection_p->name)
			free(collection_p->name);

		tmdb_clean_movie_type(collection_p->parts);

		if (collection_p->poster_path)
			free(collection_p->poster_path);

		collection_p = collection_p->next;
	}

	if (collection)
		free(collection);
}

void tmdb_clean_collection_images_type(
				tmdb_collection_images_t *collection_images)
{
	tmdb_collection_images_t *collection_images_p = collection_images;

	while (collection_images_p) {
		if (collection_images_p->id)
			free(collection_images_p->id);
		tmdb_clean_image_type(collection_images_p->backdrops);
		tmdb_clean_image_type(collection_images_p->posters);

		collection_images_p = collection_images_p->next;
	}

	if (collection_images)
		free(collection_images);
}

void tmdb_clean_country_type(tmdb_country_t *country)
{
	tmdb_country_t *country_p = country;

	while (country_p) {
		if (country_p->iso_3166_1)
			free(country_p->iso_3166_1);
		if (country_p->name)
			free(country_p->name);

		country_p = country_p->next;
	}

	if (country)
		free(country);
}

void tmdb_clean_language_type(tmdb_language_t *language)
{
	tmdb_language_t *language_p = language;

	while (language_p) {
		if (language_p->iso_639_1)
			free(language_p->iso_639_1);
		if (language_p->name)
			free(language_p->name);

		language_p = language_p->next;
	}

	if (language)
		free(language);
}

void tmdb_clean_movie_type(tmdb_movie_t *movie)
{
	tmdb_movie_t *movie_p = movie;

	while (movie_p) {
		if (movie_p->adult)
			free(movie_p->adult);
		if (movie_p->backdrop_path)
			free(movie_p->backdrop_path);
		if (movie_p->belongs_to_collection)
			free(movie_p->belongs_to_collection);
		if (movie_p->budget)
			free(movie_p->budget);
		if (movie_p->home_page)
			free(movie_p->home_page);
		if (movie_p->id)
			free(movie_p->id);
		if (movie_p->imdb_id)
			free(movie_p->imdb_id);
		if (movie_p->original_title)
			free(movie_p->original_title);
		if (movie_p->overview)
			free(movie_p->overview);
		if (movie_p->popularity)
			free(movie_p->popularity);
		if (movie_p->poster_path)
			free(movie_p->poster_path);
		if (movie_p->release_date)
			free(movie_p->release_date);
		if (movie_p->revenue)
			free(movie_p->revenue);
		if (movie_p->runtime)
			free(movie_p->runtime);
		if (movie_p->status)
			free(movie_p->status);
		if (movie_p->tagline)
			free(movie_p->tagline);
		if (movie_p->title)
			free(movie_p->title);
		if (movie_p->vote_average)
			free(movie_p->vote_average);
		if (movie_p->vote_count)
			free(movie_p->vote_count);

		tmdb_clean_genre_type(movie_p->genres);
		tmdb_clean_company_type(movie_p->production_companies);
		tmdb_clean_country_type(movie_p->production_countries);
		tmdb_clean_language_type(movie_p->spoken_languages);

		movie_p = movie_p->next;
	}
	if (movie)
		free(movie);
}
