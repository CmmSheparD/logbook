#pragma once
/*
 * Dinamic strings type.
 */
#ifndef DSTRING_H
#define DSTRING_H

#include <stdbool.h>
#include <wchar.h>

#define DSTRING_INIT_SIZE 128

/*
 * Structure representing a vector of wide characters - dynamic string.
 * Data members:
 * `raw_string` - pointer to an array allocated in the heap.
 * `len`        - length of the string stored in the vector. Has the same
 *                value as a `wcslen(raw_string)` would return.
 * `max`        - the size of an array.
 */
typedef struct DString {
	size_t len;
	size_t max;
	wchar_t *raw_string;
} dstring_t;

dstring_t *ds_createString();
void ds_freeString(dstring_t *ds);

/*
 * Ensure that every pointer is non-NULL, `len` is lesser than `max`,
 * and the last valid charater is a null-terminator.
 */
bool ds_isValid(const dstring_t *ds);

bool ds_isEmpty(const dstring_t *ds);
size_t ds_spaceAvailable(const dstring_t *ds);
/*
 * Get a size of a character string to store converted to multibyte
 * dynamic string including a terminating null character.
 */
size_t ds_multibyteLength(const dstring_t *ds);

int ds_appendChar(dstring_t *ds, wchar_t c);
int ds_appendString(dstring_t *ds, wchar_t *string);

int ds_concatStrings(dstring_t *target, dstring_t *source);

size_t ds_dumpToChars(const dstring_t *ds, char *dest, size_t n);

#endif	//DSTRING_H
