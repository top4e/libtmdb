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

#ifndef __TMDB_H_
#define __TMDB_H_

#define CHK(__a, __r)	if (__a) return (__r);

/**
* @typedef tmdb_configuration_t
* Data relevant to building image URLs.
*/
typedef struct tmdb_configuration_s {
	/** Base URL. */
	char	*base_url;
	/** Secure base URL. */
	char	*secure_base_url;
	/** String array of poster sizes. */
	char	**poster_sizes;
	/** Poster sizes count. */
	int	poster_sizes_cnt;
	/** String array of backdrop sizes. */
	char	**backdrop_sizes;
	/** Backdrop sizes count. */
	int	backdrop_sizes_cnt;
	/** String array of profile sizes. */
	char	**profile_sizes;
	/** Profile sizes count. */
	int	profile_sizes_cnt;
	/** String array of logo sizes. */
	char	**logo_sizes;
	/** Logo sizes count. */
	int	logo_sizes_cnt;
} tmdb_configuration_t;

/**
* Clean data allocated in tmdb_configuration_t structure.
*
* @param configuration Pointer to tmdb_configuration_t structure.
* @see tmdb_configuration_t
*/
void tmdb_clean_configuration(tmdb_configuration_t *configuration);

/**
* @typedef tmdb_person_t
* Person data.
*/
typedef struct tmdb_person_s {
	/** Adult movies. */
	char			*adult;
	/** Array of nicknames. */
	char			**also_known_as;
	/** Nicknames count. */
	int			aka_cnt;
	/** Biography. */
	char			*biography;
	/** Date of birth. */
	char			*birthday;
	/** Date of death. */
	char			*deathday;
	/** WEB homepage. */
	char			*homepage;
	/** Specific person id. */
	char			*id;
	/** Person name. */
	char			*name;
	/** Place of birth. */
	char			*place_of_birth;
	/** Profile image. */
	char			*profile_path;
	/** Next element. */
	struct tmdb_person_s	*next;
} tmdb_person_t;

/**
* Clean data allocated in tmdb_person_t structure.
*
* @param person Pointer to tmdb_person_t structure.
* @see tmdb_person_t
*/
void tmdb_clean_person_type(tmdb_person_t *person);

/**
* @typedef tmdb_company_t
* Company data.
*/
typedef struct tmdb_company_s {
	/** Company description. */
	char			*description;
	/** Address. */
	char			*headquarters;
	/** WEB homepage. */
	char			*homepage;
	/** Specific company id. */
	char			*id;
	/** Company name. */
	char			*name;
	/** Company logo image. */
	char			*logo_path;
	/** Parent company. */
	struct tmdb_company_s	*parent_company;
	/** Next element. */
	struct tmdb_company_s	*next;
} tmdb_company_t;

/**
* Clean data allocated in tmdb_company_t structure.
*
* @param company Pointer to tmdb_company_t structure.
* @see tmdb_company_t
*/
void tmdb_clean_company_type(tmdb_company_t *company);

/**
* @typedef auth_token_t
* Authentication token data.
*/
typedef struct auth_token_s {
	/** Date of expiration. */
	char	*expires_at;
	/** Token. */
	char	*token;
} auth_token_t;

/**
* Clean data allocated in auth_token_t structure.
*
* @param auth_token Pointer to auth_token_t structure.
* @see auth_token_t
*/
void tmdb_clean_auth_token_type(auth_token_t *auth_token);

/**
* @typedef tmdb_genre_t
* Genre data.
*/
typedef struct tmdb_genre_s {
	/** Specific genre id. */
	char			*id;
	/** Genre name. */
	char			*name;
	/** Next element. */
	struct tmdb_genre_s	*next;
} tmdb_genre_t;

/**
* Clean data allocated in tmdb_genre_t structure.
*
* @param genre_list Pointer to tmdb_genre_t structure.
* @see tmdb_genre_t
*/
void tmdb_clean_genre_type(tmdb_genre_t *genre_list);

/**
* @typedef tmdb_country_t
* Country info data.
*/
typedef struct tmdb_country_s {
	/** ISO 3166-1 code. */
	char			*iso_3166_1;
	/** Country name. */
	char			*name;
	/** Next element. */
	struct tmdb_country_s	*next;
} tmdb_country_t;

/**
* Clean data allocated in tmdb_country_t structure.
*
* @param country Pointer to tmdb_country_t structure.
* @see tmdb_country_t
*/
void tmdb_clean_country_type(tmdb_country_t *country);

/**
* @typedef tmdb_language_t
* Language info data.
*/
typedef struct tmdb_language_s {
	/** ISO 639-1 code. */
	char			*iso_639_1;
	/** Language name. */
	char			*name;
	/** Next element. */
	struct tmdb_language_s	*next;
} tmdb_language_t;

/**
* Clean data allocated in tmdb_language_t structure.
*
* @param language Pointer to tmdb_language_t structure.
* @see tmdb_language_t
*/
void tmdb_clean_language_type(tmdb_language_t *language);

/**
* @typedef tmdb_movie_t
* Basic movie info data.
*/
typedef struct tmdb_movie_s {
	/** Adult movie. */
	char				*adult;
	/** Movie backdrop image. */
	char				*backdrop_path;
	/** TBD . */
	char				*belongs_to_collection;
	/** Movie budged. */
	char				*budget;
	/** Movie genres. */
	tmdb_genre_t			*genres;
	/** Movie WEB homepage. */
	char				*home_page;
	/** Specific movie id. */
	char				*id;
	/** IMDd id. */
	char				*imdb_id;
	/** Original movie title. */
	char				*original_title;
	/** Movie overview. */
	char				*overview;
	/** Movie popularity. */
	char				*popularity;
	/** Movie poster image. */
	char				*poster_path;
	/** Production companies. */
	tmdb_company_t			*production_companies;
	/** Production countries. */
	tmdb_country_t			*production_countries;
	/** Release date. */
	char				*release_date;
	/** Ravenue. */
	char				*revenue;
	/** Movie runtime. */
	char				*runtime;
	/** Movie spoken languages. */
	tmdb_language_t			*spoken_languages;
	/** Movie release status. */
	char				*status;
	/** Movie tagline. */
	char				*tagline;
	/** Movie title. */
	char				*title;
	/** Average vote. */
	char				*vote_average;
	/** Vote count. */
	char				*vote_count;
	/** Next element */
	struct tmdb_movie_s		*next;
} tmdb_movie_t;

/**
* Clean data allocated in tmdb_movie_t structure.
*
* @param movie_basic_info Pointer to tmdb_movie_t structure.
* @see tmdb_movie_t
*/
void tmdb_clean_movie_type(tmdb_movie_t *movie_basic_info);

/**
* @typedef tmdb_cast_t
* Cast info data.
*/
typedef struct tmdb_cast_s {
	/** Specific person id. */
	char			*id;
	/** Actor name. */
	char			*name;
	/** Character name. */
	char			*character;
	/** ???. */
	char			*order;
	/** Specific cast id. */
	char			*cast_id;
	/** Actor profile image. */
	char			*profile_path;
	/** Next element. */
	struct tmdb_cast_s	*next;
} tmdb_cast_t;

/**
* Clean data allocated in tmdb_cast_t structure.
*
* @param cast Pointer to tmdb_cast_t structure.
* @see tmdb_cast_t
*/
void tmdb_clean_cast_type(tmdb_cast_t *cast);

/**
* @typedef tmdb_crew_t
* Crew info data.
*/
typedef struct tmdb_crew_s {
	/** Specific person id. */
	char			*id;
	/** Person name. */
	char			*name;
	/** Department. */
	char			*department;
	/** Job. */
	char			*job;
	/** Person profile image. */
	char			*profile_path;
	/** Next element. */
	struct tmdb_crew_s	*next;
} tmdb_crew_t;

/**
* Clean data allocated in tmdb_crew_t structure.
*
* @param crew Pointer to tmdb_crew_t structure.
* @see tmdb_crew_t
*/
void tmdb_clean_crew_type(tmdb_crew_t *crew);

/**
* @typedef tmdb_movie_casts_t
* Movie casts data.
*/
typedef struct tmdb_movie_casts_s {
	/** ???. */
	char				*id;
	/** Casts. */
	tmdb_cast_t			*cast;
	/** Crew. */
	tmdb_crew_t			*crew;
	/** Next element. */
	struct tmdb_movie_casts_s	*next;
} tmdb_movie_casts_t;

/**
* Clean data allocated in tmdb_movie_casts_t structure.
*
* @param movie_casts Pointer to tmdb_movie_casts_t structure.
* @see tmdb_movie_casts_t
*/
void tmdb_clean_movie_casts_type(tmdb_movie_casts_t *movie_casts);

/**
* @typedef tmdb_image_t
* Image basic data.
*/
typedef struct tmdb_image_s {
	/** Filename. */
	char			*file_path;
	/** Image width. */
	char			*width;
	/** Image height. */
	char			*height;
	/** ISO 639-1 code. */
	char			*iso_639_1;
	/** Aspect ratio. */
	char			*aspect_ratio;
	/** Average vote. */
	char			*vote_average;
	/** Vote count. */
	char			*vote_count;
	/** Next element. */
	struct tmdb_image_s	*next;
} tmdb_image_t;

/**
* Clean data allocated in tmdb_image_t structure.
*
* @param image Pointer to tmdb_image_t structure.
* @see tmdb_image_t
*/
void tmdb_clean_image_type(tmdb_image_t *image);

/**
* @typedef tmdb_person_credits_t
* Person credits data.
*/
typedef struct tmdb_person_credits_s {
	/** Movie name. */
	tmdb_movie_t			*movie;
	/** Character name. */
	char				*character;
	/** Next element. */
	struct tmdb_person_credits_s	*next;
} tmdb_person_credits_t;

/**
* Clean data allocated in tmdb_person_credits_t structure.
*
* @param person_credits Pointer to tmdb_person_credits_t structure.
* @see tmdb_person_credits_t
*/
void tmdb_clean_person_credits_type(tmdb_person_credits_t *person_credits);

/**
* @typedef tmdb_release_t
* Release info data.
*/
typedef struct tmdb_release_s {
	/** ISO 3166-1 code. */
	char			*iso_3166_1;
	/** Certification. */
	char			*certification;
	/** Release date. */
	char			*release_date;
	/** Next element. */
	struct tmdb_release_s	*next;
} tmdb_release_t;

/**
* Clean data allocated in tmdb_release_t structure.
*
* @param release Pointer to tmdb_release_t structure.
* @see tmdb_release_t
*/
void tmdb_clean_release_type(tmdb_release_t *release);

/**
* @typedef tmdb_movie_images_t
* Movie images data.
*/
typedef struct tmdb_movie_images_s {
	/** Specific movie id. */
	char				*id;
	/** Movie backdrop images. */
	tmdb_image_t			*backdrops;
	/** Movie poster images. */
	tmdb_image_t			*posters;
	/** Next element. */
	struct tmdb_movie_images_s	*next;
} tmdb_movie_images_t;

/**
* Clean data allocated in tmdb_movie_images_t structure.
*
* @param movie_images Pointer to tmdb_movie_images_t structure.
* @see tmdb_movie_images_t
*/
void tmdb_clean_movie_images_type(tmdb_movie_images_t *movie_images);

/**
* @typedef tmdb_keywords_t
* Keyword info data.
*/
typedef struct tmdb_keywords_s {
	/** Specific keyword id. */
	char			*id;
	/** Keyword name. */
	char			*name;
	/** Next element. */
	struct tmdb_keywords_s	*next;
} tmdb_keywords_t;

/**
* Clean data allocated in tmdb_keywords_t structure.
*
* @param keywords Pointer to tmdb_keywords_t structure.
* @see tmdb_keywords_t
*/
void tmdb_clean_keywords_type(tmdb_keywords_t *keywords);

/**
* @typedef tmdb_movie_keywords_t
* Movie keywords data.
*/
typedef struct tmdb_movie_keywords_s {
	/** Specific movie id. */
	char				*id;
	/** Movie keywords. */
	tmdb_keywords_t			*keywords;
	/** Next element. */
	struct tmdb_movie_keywords_s	*next;
} tmdb_movie_keywords_t;

/**
* Clean data allocated in tmdb_movie_keywords_t structure.
*
* @param movie_keywords Pointer to tmdb_movie_keywords_t structure.
* @see tmdb_movie_keywords_t
*/
void tmdb_clean_movie_keywords_type(tmdb_movie_keywords_t *movie_keywords);

/**
* @typedef tmdb_movie_releases_t
* Movie releases data.
*/
typedef struct tmdb_movie_releases_s {
	/** Specific movie id. */
	char				*id;
	/** Movie releases. */
	tmdb_release_t			*releases;
	/** Next element. */
	struct tmdb_movie_releases_s	*next;
} tmdb_movie_releases_t;

/**
* Clean data allocated in tmdb_movie_releases_t structure.
*
* @param movie_releases Pointer to tmdb_movie_releases_t structure.
* @see tmdb_movie_releases_t
*/
void tmdb_clean_movie_releases_type(tmdb_movie_releases_t *movie_releases);

/**
* @typedef tmdb_trailer_t
* Trailer info data.
*/
typedef struct tmdb_trailer_s {
	/** Trailer name. */
	char			*name;
	/** Trailer movie size. */
	char			*size;
	/** Trailer URL. */
	char			*source;
	/** Next element. */
	struct tmdb_trailer_s	*next;
} tmdb_trailer_t;

/**
* Clean data allocated in tmdb_trailer_t structure.
*
* @param trailer Pointer to tmdb_trailer_t structure.
* @see tmdb_trailer_t
*/
void tmdb_clean_trailer_type(tmdb_trailer_t *trailer);

/**
* @typedef tmdb_movie_trailers_t
* Movie trailers data.
*/
typedef struct tmdb_movie_trailers_s {
	/** Specific movie id. */
	char				*id;
	/** QuickTime trailers. */
	tmdb_trailer_t			*quicktime;
	/** YouTube trailers. */
	tmdb_trailer_t			*youtube;
	/** Next element. */
	struct tmdb_movie_trailers_s	*next;
} tmdb_movie_trailers_t;

/**
* Clean data allocated in tmdb_movie_trailers_t structure.
*
* @param movie_trailers Pointer to tmdb_movie_trailers_t structure.
* @see tmdb_movie_trailers_t
*/
void tmdb_clean_movie_trailers_type(tmdb_movie_trailers_t *movie_trailers);

/**
* @typedef tmdb_translation_t
* Translation info data.
*/
typedef struct tmdb_translation_s {
	/** ISO 639-1 code. */
	char				*iso_639_1;
	/** Language original name. */
	char				*name;
	/** Language english name. */
	char				*english_name;
	/** Next element. */
	struct tmdb_translation_s	*next;
} tmdb_translation_t;

/**
* Clean data allocated in tmdb_translation_t structure.
*
* @param translation Pointer to tmdb_translation_t structure.
* @see tmdb_translation_t
*/
void tmdb_clean_translation_type(tmdb_translation_t *translation);

/**
* @typedef tmdb_movie_translations_t
* Movie translations data.
*/
typedef struct tmdb_movie_translations_s {
	/** Specific movie id. */
	char					*id;
	/** Movie translations. */
	tmdb_translation_t			*translations;
	/** Next element. */
	struct tmdb_movie_translations_s	*next;
} tmdb_movie_translations_t;

/**
* Clean data allocated in tmdb_movie_translations_t structure.
*
* @param movie_translations Pointer to tmdb_movie_translations_t structure.
* @see tmdb_movie_translations_t
*/
void tmdb_clean_movie_translations_type(
				tmdb_movie_translations_t *movie_translations);

/**
* @typedef tmdb_collection_t
* Collection info data.
*/
typedef struct tmdb_collection_s {
	/** Movie collection image. */
	char				*backdrop_path;
	/** Specific collection id. */
	char				*id;
	/** Collection name. */
	char				*name;
	/** Collection movies. */
	tmdb_movie_t			*parts;
	/** Collection poster image. */
	char				*poster_path;
	/** Next element. */
	struct tmdb_collection_s	*next;
} tmdb_collection_t;

/**
* Clean data allocated in tmdb_collection_t structure.
*
* @param collection Pointer to tmdb_collection_t structure.
* @see tmdb_collection_t
*/
void tmdb_clean_collection_type(tmdb_collection_t *collection);

/**
* @typedef tmdb_collection_images_t
* Movie collections data.
*/
typedef struct tmdb_collection_images_s {
	/** Specific collection id. */
	char				*id;
	/** Collection backdrop images. */
	tmdb_image_t			*backdrops;
	/** Collection poster images. */
	tmdb_image_t			*posters;
	/** Next element. */
	struct tmdb_collection_images_s	*next;
} tmdb_collection_images_t;

/**
* Clean data allocated in tmdb_collection_images_t structure.
*
* @param collection_images Pointer to tmdb_collection_images_t structure.
* @see tmdb_collection_images_t
*/
void tmdb_clean_collection_images_type(
				tmdb_collection_images_t *collection_images);


/**
* Get the system wide configuration information.
*
* @return Configuration.
*
* Some elements of the API require some knowledge of this configuration data.
* The purpose of this is to try and keep the actual API responses
* as light as possible. It is recommended you store this data within your
* application and check for updates every so often.
* This method currently holds the data relevant to building image URLs
* as well as the change key map.
*  To build an image URL, you will need 3 pieces of data.
* The base_url, size and file_path. Simply combine them all
* and you will have a fully qualified URL. Here’s an example URL:
* http://cf2.imgobject.com/t/p/w500/8uO0gUM8aNqYLs1OsTBQiXu0fEv.jpg
*
* @see tmdb_configuration_t
*/
tmdb_configuration_t *tmdb_configuration(void);

/**
* Search for movies by title.
*
* @param  name     Movie tilte to search for.
* @param  language ISO 639-1 code.
* @param  adult    Toggle the inclusion of adult titles.
* @param  year     Filter results to only include this value.
* @return List of movies found.
* @see tmdb_movie_t
*/
tmdb_movie_t *tmdb_search_movie(const char	*name,
				const char	*language,
				int		adult,
				const char	*year);

/**
* Search for people by name.
*
* @param name
* @param adult
* @return
* @see tmdb_person_t
*/
tmdb_person_t *tmdb_search_person(const char	*name,
				  int		adult);

/**
* Search for companies by name.
*
* @param name
* @return
* @see tmdb_company_t
*/
tmdb_company_t *tmdb_search_company(const char *name);

/**
* TBD
*
*/
auth_token_t *tmdb_auth_new_token(void);

/**
* TBD
*
*/
int tmdb_auth_new_session(char *request_token);

/**
* Get the basic movie information for a specific movie id.
*
* @param movie_id Specific movie ID.
* @param language ISO 639-1 code.
* @return
* @see movie_basic_info_t
* @see tmdb_search_movie
*/
tmdb_movie_t *tmdb_movie_info(const char	*movie_id,
				    const char	*language);

/**
* Get the alternative titles for a specific movie id.
*
* @param movie_id Specific movie ID.
* @param country  ISO 3166-1 code.
* @return
* @see tmdb_movie_t
* @see tmdb_search_movie
*/
tmdb_movie_t *tmdb_movie_alt_titles(const char *movie_id,
				    const char *country);

/**
* Get the cast information for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_casts_t
* @see tmdb_search_movie
*/
tmdb_movie_casts_t *tmdb_movie_casts(const char *movie_id);

/**
* Get the changes for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
*
* Changes are grouped by key, and ordered by date in descending order.
* The language is present on fields that are translatable.
*
* @see tmdb_movie_changes_t
* @see tmdb_search_movie
*/
int tmdb_movie_changes(const char *movie_id);

/**
* Get the images (posters and backdrops) for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_images_t
* @see tmdb_search_movie
*/
tmdb_movie_images_t *tmdb_movie_images(const char *movie_id);

/**
* Get the plot keywords for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_keywords_t
* @see tmdb_search_movie
*/
tmdb_movie_keywords_t *tmdb_movie_keywords(const char *movie_id);

/**
* Get the release date by country for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_releases_t
* @see tmdb_search_movie
*/
tmdb_movie_releases_t *tmdb_movie_releases(const char *movie_id);

/**
* Get the trailers for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_trailers_t
* @see tmdb_search_movie
*/
tmdb_movie_trailers_t *tmdb_movie_trailers(const char *movie_id);

/**
* Get the translations for a specific movie id.
*
* @param movie_id Specific movie ID.
* @return
* @see tmdb_movie_translations_t
* @see tmdb_search_movie
*/
tmdb_movie_translations_t *tmdb_movie_translations(const char *movie_id);

/**
* Get the similar movies for a specific movie id.
*
* @param movie_id Specific movie ID.
* @param language ISO 639-1 code.
* @return
* @see tmdb_movie_t
* @see tmdb_search_movie
*/
tmdb_movie_t *tmdb_movie_similar(const char *movie_id,
				 const char *language);

/**
* Get the list of upcoming movies.
*
* @param language ISO 639-1 code.
* @return
*
* This list refreshes every day.
* The maximum number of items this list will include is 100.
*
* @see tmdb_movie_t
*/
tmdb_movie_t *tmdb_movie_upcoming(const char *language);

/**
* Get the list of movies playing in theatres.
*
* @param language ISO 639-1 code.
* @return
*
*  This list refreshes every day.
* The maximum number of items this list will include is 100.
*
* @see tmdb_movie_t
*/
tmdb_movie_t *tmdb_movie_now_playing(const char *language);

/**
* Get the list of popular movies on The Movie Database.
*
* @param language ISO 639-1 code.
* @return
*
* This list refreshes every day.
*
* @see tmdb_movie_t
*/
tmdb_movie_t *tmdb_movie_popular(const char *language);

/**
* Get the list of top rated movies.
*
* @param language ISO 639-1 code.
* @return
*
* By default, this list will only include movies that have 10 or more votes.
* This list refreshes every day.
*
* @see tmdb_movie_t
*/
tmdb_movie_t *tmdb_movie_top_rated(const char *language);

/**
* Get the basic information about a company.
*
* @param company_id Specific company ID.
* @return
* @see tmdb_company_t
* @see tmdb_search_company
*/
tmdb_company_t *tmdb_company_info(const char *company_id);

/**
* Get the list of movies associated with a particular company.
*
* @param company_id Specific company ID.
* @param language ISO 639-1 code.
* @param page
* @return
* @see tmdb_movie_t
* @see tmdb_search_company
*/
tmdb_movie_t *tmdb_company_movies(const char *company_id,
				  const char *language,
				  const char *page);
/**
* Get the basic collection information for a specific collection id.
*
* @param collection_id Specific collection ID.
* @param language ISO 639-1 code.
* @return
*
* You can get the ID needed for this function by calling a
* @tmdb_movie_info() and paying attention to
* the belongs_to_collection field.
* Movie parts are not sorted in any particular order.
* If you would like to sort them yourself you can use
* the provided release_date field.
*
* @see tmdb_collection_t
*/
tmdb_collection_t *tmdb_collection_info(const char *collection_id,
					const char *language);

/**
* Get all of the images for a particular collection by collection id.
*
* @param collection_id Specific collection ID.
* @param language ISO 639-1 code.
* @return
* @see tmdb_collection_images_t
*/
tmdb_collection_images_t *tmdb_collection_images(const char *collection_id,
						 const char *language);

/**
* Get the list of genres.
*
* @param language ISO 639-1 code.
* @return
* @see tmdb_genre_t
*/
tmdb_genre_t *tmdb_genre_list(const char *language);

/**
* Get the list of movies for a particular genre by id.
*
* @param genre_id Specific genre ID.
* @param language ISO 639-1 code.
* @param page
* @return
* @see tmdb_movie_t
* @see tmdb_genre_list
*
* Only movies with 10 or more votes are included.
*/
tmdb_movie_t *tmdb_genre_movies(const char *genre_id,
				const char *language,
				const char *page);
/**
* Get the general person information for a specific id.
*
* @param person_id Specific person ID.
* @return
* @see tmdb_person_t
* @see tmdb_search_person
*/
tmdb_person_t *tmdb_person_info(const char *person_id);

/**
* Get the credits for a specific person id.
*
* @param person_id Specific person ID.
* @return
* @see tmdb_person_credits_t
* @see tmdb_search_person
*/
tmdb_person_credits_t *tmdb_person_credits(const char *person_id);

/**
* Get the images for a specific person id.
*
* @param person_id Specific person ID.
* @return
* @see tmdb_image_t
* @see tmdb_search_person
*/
tmdb_image_t *tmdb_person_images(const char *person_id);

/**
* Get the latest person id.
*
* @return
* @see tmdb_person_t
*/
tmdb_person_t *tmdb_person_latest(void);

typedef struct MemoryStruct_s {
	char *memory;
	size_t size;
} MemoryStruct_t;

typedef struct net_data_s {
	MemoryStruct_t	header;
	MemoryStruct_t	body;
	size_t		body_offset;
	int		err_code;
} net_data_t;

typedef struct tmdb_ctx_s {
	int (*net_get)(const char *url_name,
		       const char *header_str,
		       net_data_t *data);
	void (*net_init_data)(net_data_t *data);
	void (*net_free_data)(net_data_t *data);
	char *api_key;
} tmdb_ctx_t;

/**
* Initialize libtmdb internal context structure.
*
* @return 0 on success, negative on error.
* @see tmdb_ctx_t
*/
int tmdb_init(tmdb_ctx_t *ctx);

#endif
