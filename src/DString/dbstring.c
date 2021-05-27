#include "dbstring.h"

#include <stdlib.h>
#include <string.h>

int _dbs_reallocInnerString(dbstring_t *dbs, size_t delta)
{
	if (!dbs)
		return -1;
	dbs->max += delta == 0 ? DBSTRING_INIT_SIZE :
		(delta / DBSTRING_INIT_SIZE + !(delta % DBSTRING_INIT_SIZE == 0))
		* DBSTRING_INIT_SIZE;
	dbs->raw_string = realloc(dbs->raw_string,
		dbs->max * sizeof(*dbs->raw_string));
	return 0;
}

dbstring_t *dbs_createString()
{
	dbstring_t *str = malloc(sizeof(*str));
	str->len = 0;
	str->max = DBSTRING_INIT_SIZE;
	str->raw_string = malloc(str->max * sizeof(*str->raw_string));
	str->raw_string[0] = '\0';
	return str;
}

void dbs_freeString(dbstring_t *dbs)
{
	if (!dbs)
		return;
	if (dbs->raw_string)
		free(dbs->raw_string);
	free(dbs);
}


bool dbs_isValid(const dbstring_t *dbs)
{
	return (
		dbs
		&& dbs->raw_string
		&& dbs->len < dbs->max
		&& dbs->raw_string[dbs->len] == '\0'
	);
}


bool dbs_isEmpty(const dbstring_t *dbs)
{
	return dbs->len == 0;
}

size_t dbs_spaceAvalable(const dbstring_t *dbs)
{
	if (!dbs_isValid(dbs))
		return 0;
	return dbs->max - dbs->len - 1;
}

size_t dbs_reserve(dbstring_t *dbs, size_t least)
{
	if (!dbs_isValid(dbs))
		return 0;
	if (least > dbs->max)
		_dbs_reallocInnerString(dbs, least - dbs->max);
	return dbs->max;
}

size_t dbs_wideLength(const dbstring_t *dbs)
{
	if (!dbs_isValid(dbs))
		return 0;
	return mbstowcs(NULL, dbs->raw_string, 0);
}


int dbs_appendChar(dbstring_t *dbs, char c)
{
	if (!dbs_isValid(dbs))
		return -1;
	if (dbs_spaceAvalable(dbs) == 0)
		_dbs_reallocInnerString(dbs, 0);
	if (dbs->len != 0)
		--dbs->len;
	dbs->raw_string[dbs->len] = c;
	dbs->raw_string[dbs->len + 1] = '\0';
	dbs->len += 2;
	return 0;
}

int dbs_appendString(dbstring_t *dbs, char *string)
{
	if (!dbs_isValid(dbs) || !string)
		return -1;
	size_t len = wcslen(string);
	size_t avail = dbs_spaceAvalable(dbs);
	if (avail < len) {
		_dbs_reallocInnerString(dbs, len - avail);
	}
	wcscat(dbs->raw_string, string);
	dbs->len += len;
	return 0;
}


int dbs_concatStrings(dbstring_t *target, dbstring_t *source)
{
	if (!dbs_isValid(target) || !dbs_isValid(source))
		return -1;
	return dbs_appendString(target, source->raw_string);
}


size_t dbs_dumpToWide(const dbstring_t *dbs, wchar_t *dest, size_t n)
{
	if (!dbs_isValid(dbs) || !dest)
		return 0;
	return mbstowcs(dest, dbs->raw_string, n);
}
