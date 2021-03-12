#include <stdlib.h>

#include "dstring.h"

int _ds_reallocInnerString(dstring_t *ds, size_t delta)
{
	if (!ds) return -1;
	ds->max += delta == 0 ? DSTRING_INIT :
		delta / DSTRING_INIT + !(delta % DSTRING_INIT == 0);
	ds->string = realloc(ds->string, ds->max * sizeof(*ds->string));
	return 0;
}

dstring_t *ds_createString()
{
	dstring_t *str = malloc(sizeof(*str));
	str->size = 0;
	str->max = DSTRING_INIT;
	str->string = malloc(str->max * sizeof(*str->string));
	str->string[0] = '\0';
	return str;
}

void ds_freeString(dstring_t *ds)
{
	if (!ds) return;
	if (ds->string)
		free(ds->string);
	free(ds);
}

bool ds_isEmpty(const dstring_t *ds)
{
	if (ds->size == 0)
		return true;
	else
		return false;
}

int ds_appendChar(dstring_t *ds, wchar_t c)
{
	if (!ds || !ds->string) return -1;
	if (ds->size + 1 >= ds->max)
		_ds_reallocInnerString(ds, 0);
	if (ds->size != 0)
		--ds->size;
	ds->string[ds->size] = c;
	ds->string[ds->size + 1] = '\0';
	ds->size += 2;
	return 0;
}

int ds_appendString(dstring_t *ds, wchar_t *string)
{
	if (!ds || !ds->string || !string) return -1;
	size_t len = wcslen(string);
	size_t avail = ds->max - ds->size;
	if (avail < len) {
		_ds_reallocInnerString(ds, len - avail);
	}
	wcscat(ds->string, string);
	return 0;
}
