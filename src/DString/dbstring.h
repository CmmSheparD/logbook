#pragma once
#ifndef DBSTRING_H
#define DBSTRING_H

#include <stdbool.h>
#include <wchar.h>

#define DBSTRING_INIT_SIZE 128

/*
 * Structure representing a vector of chars - dynamic byte string.
 * Data members:
 * `raw_string` - pointer to an array allocated in the heap.
 * `len`	- lenght of the string stored in `raw_string`. Has the same
 * 		  value as `strlen(raw_string)` would return.
 * `max`	- the size of an array.
 */
typedef struct DBString {
	size_t len;
	size_t max;
	char *raw_string;
} dbstring_t;

dbstring_t *dbs_createString();
void dbs_freeString(dbstring_t *dbs);

/*
 * Ensure that every pointer is non-NULL, `len` is lesser than `max`,
 * and the last valid charater is a null-terminator.
 */
bool dbs_isValid(const dbstring_t *dbs);

bool dbs_isEmpty(const dbstring_t *dbs);
size_t dbs_spaceAvalable(const dbstring_t *dbs);
size_t dbs_reserve(dbstring_t *dbs, size_t least);
/*
 * Get a size of a wide character string to store converted to wide character
 * dynamic string including a terminating null character.
 */
size_t dbs_wideLength(const dbstring_t *dbs);

int dbs_appendChar(dbstring_t *dbs, char c);
int dbs_appendString(dbstring_t *dbs, char *string);

int dbs_concatStrings(dbstring_t *target, dbstring_t *source);

size_t dbs_dumpToWide(const dbstring_t *dbs, wchar_t *dest, size_t n);

#endif	// DBSTRING_H
