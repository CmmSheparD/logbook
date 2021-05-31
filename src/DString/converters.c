#include "converters.h"

#include <stdlib.h>

int dcv_convertToBytes(const dstring_t *src, dbstring_t *dest)
{
	if (!ds_isValid(src) || !dbs_isValid(dest))
		return -1;
	size_t dlen = ds_multibyteLength(src);
	dbs_reserve(dest, dlen);
	wcstombs(dest->raw_string, src->raw_string, dlen);
	return 0;
}

int dcv_convertToWide(const dbstring_t *src, dstring_t *dest)
{
	if (!dbs_isValid(src) || !ds_isValid(dest))
		return -1;
	size_t dlen = dbs_wideLength(src);
	ds_reserve(dest, dlen);
	wcstombs(dest->raw_string, src->raw_string, dlen);
}
