AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = \
-I. \
-I$(top_builddir) \
-I$(top_srcdir) \
-I$(top_srcdir)/src/lib \
-I$(top_builddir)/src/lib

lib_LTLIBRARIES = libtmdb.la

includes_HEADERS = \
tmdb.h
includesdir = $(includedir)/tmdb-@VMAJ@

includesunstable_HEADERS = \
tmdb.h
includesunstabledir = $(includedir)/tmdb-@VMAJ@

includesub_HEADERS = \
tmdb.h
includesubdir = $(includedir)/tmdb-@VMAJ@/

libtmdb_la_SOURCES = \
auth_new_session.c \
auth_new_session.h \
auth_new_token.c \
auth_new_token.h \
collection_images.c \
collection_images.h \
collection_info.c \
collection_info.h \
company_info.c \
company_info.h \
company_movies.c \
company_movies.h \
configuration.c \
configuration.h \
genre_list.c \
genre_list.h \
genre_movies.c \
genre_movies.h \
jsmn.c \
jsmn.h \
movie_alt.c \
movie_alt.h \
movie_casts.c \
movie_casts.h \
movie_changes.c \
movie_changes.h \
movie_images.c \
movie_images.h \
movie_info.c \
movie_info.h \
movie_keywords.c \
movie_keywords.h \
movie_latest.c \
movie_latest.h \
movie_now_playing.c \
movie_now_playing.h \
movie_popular.c \
movie_popular.h \
movie_rating.c \
movie_rating.h \
movie_releases.c \
movie_releases.h \
movie_similar.c \
movie_similar.h \
movie_top_rated.c \
movie_top_rated.h \
movie_trailers.c \
movie_trailers.h \
movie_translations.c \
movie_translations.h \
movie_upcoming.c \
movie_upcoming.h \
parser.c \
parser.h \
person_changes.c \
person_changes.h \
person_credits.c \
person_credits.h \
person_images.c \
person_images.h \
person_info.c \
person_info.h \
person_latest.c \
person_latest.h \
search_company.c \
search_company.h \
search_movie.c \
search_movie.h \
search_person.c \
search_person.h \
data.c \
data.h


libtmdb_la_CFLAGS = \
-DJSMN_PARENT_LINKS \
-DJSMN_STRICT \
-Wall \
-Werror

libtmdb_la_LIBADD =

libtmdb_la_LDFLAGS =

EXTRA_DIST =
