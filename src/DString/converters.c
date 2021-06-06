#include "converters.h"

#include <stdlib.h>

size_t dbs_reserve(dbstring_t *dbs, size_t least);
size_t ds_reserve(dstring_t *ds, size_t least);


int dcv_convertToBytes(const dstring_t *src, dbstring_t *dest)
{
	if (!ds_isValid(src) || !dbs_isValid(dest))
		return -1;
	dest->len = ds_multibyteLength(src) - 1;
	dbs_reserve(dest, dest->len);
	wcstombs(dest->raw_string, src->raw_string, dest->len);
	dest->raw_string[dest->len] = '\0';
	return 0;
}

int dcv_convertToWide(const dbstring_t *src, dstring_t *dest)
{
	if (!dbs_isValid(src) || !ds_isValid(dest))
		return -1;
	dest->len = dbs_wideLength(src) - 1;
	ds_reserve(dest, dest->len);
	mbstowcs(dest->raw_string, src->raw_string, dest->len);
	dest->raw_string[dest->len] = L'\0';
	return 0;
}
