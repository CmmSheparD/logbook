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
	if (!ds) return;
	if (ds->raw_string)
		free(ds->raw_string);
	free(ds);
}

bool ds_isEmpty(const dstring_t *ds)
{
	if (ds->len == 0)
		return true;
	else
		return false;
}

size_t ds_spaceAvalable(const dstring_t *ds)
{
	return ds->max - ds->len - 1;
}

int ds_appendChar(dstring_t *ds, wchar_t c)
{
	if (!ds || !ds->raw_string) return -1;
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
	if (!ds || !ds->raw_string || !string) return -1;
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
	if (!target || !source) return -1;
	return ds_appendString(target, source->raw_string);
}
