#include "dstring.h"

#include <stdlib.h>

int _ds_reallocInnerString(dstring_t *ds, size_t delta)
{
	if (!ds) return -1;
	ds->max += delta == 0 ? DSTRING_INIT_SIZE :
		(delta / DSTRING_INIT_SIZE + !(delta % DSTRING_INIT_SIZE == 0))
		* DSTRING_INIT_SIZE;
	ds->raw_string = realloc(ds->raw_string,
		ds->max * sizeof(*ds->raw_string));
	return 0;
}

dstring_t *ds_createString()
{
	dstring_t *str = malloc(sizeof(*str));
	str->len = 0;
	str->max = DSTRING_INIT_SIZE;
	str->raw_string = malloc(str->max * sizeof(*str->raw_string));
	str->raw_string[0] = '\0';
	return str;
}

void ds_freeString(dstring_t *ds)
{
	if (!ds)
		return;
	if (ds->raw_string)
		free(ds->raw_string);
	free(ds);
}


bool ds_isValid(const dstring_t *ds)
{
	return (
		ds
		&& ds->raw_string
		&& ds->len < ds->max
		&& ds->raw_string[ds->len] == '\0'
	);
}


bool ds_isEmpty(const dstring_t *ds)
{
	return ds->len == 0;
}

size_t ds_spaceAvalable(const dstring_t *ds)
{
	if (!ds_isValid(ds))
		return 0;
	return ds->max - ds->len - 1;
}

size_t ds_reserve(dstring_t *ds, size_t least)
{
	if (!ds_isValid(ds))
		return 0;
	if (least > ds->max)
		_ds_reallocInnerString(ds, least - ds->max);
	return ds->max;
}

size_t ds_multibyteLength(const dstring_t *ds)
{
	if (!ds_isValid(ds))
		return 0;
	return wcstombs(NULL, ds->raw_string, 0) + 1;
}


int ds_appendChar(dstring_t *ds, wchar_t c)
{
	if (!ds_isValid(ds))
		return -1;
	if (ds_spaceAvalable(ds) == 0)
		_ds_reallocInnerString(ds, 0);
	if (ds->len != 0)
		--ds->len;
	ds->raw_string[ds->len] = c;
	ds->raw_string[ds->len + 1] = '\0';
	ds->len += 2;
	return 0;
}

int ds_appendString(dstring_t *ds, wchar_t *string)
{
	if (!ds_isValid(ds) || !string)
		return -1;
	size_t len = wcslen(string);
	size_t avail = ds_spaceAvalable(ds);
	if (avail < len) {
		_ds_reallocInnerString(ds, len - avail);
	}
	wcscat(ds->raw_string, string);
	ds->len += len;
	return 0;
}


int ds_concatStrings(dstring_t *target, dstring_t *source)
{
	if (!ds_isValid(target) || !ds_isValid(source))
		return -1;
	return ds_appendString(target, source->raw_string);
}


size_t ds_dumpToChars(const dstring_t *ds, char *dest, size_t n)
{
	if (!ds_isValid(ds) || !dest)
		return 0;
	return wcstombs(dest, ds->raw_string, n);
}
