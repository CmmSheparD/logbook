#pragma once
/*
 * Dinamic strings type.
 */
#ifndef DSTRING_H
#define DSTRING_H

#include <stdbool.h>
#include <wchar.h>

#define DSTRING_INIT 128

typedef struct DString {
	size_t size, max;
	wchar_t *string;
} dstring_t;

dstring_t *ds_createString();

void ds_freeString(dstring_t *ds);

bool ds_isEmpty(const dstring_t *ds);

int ds_appendChar(dstring_t *ds, wchar_t c);

int ds_appendString(dstring_t *ds, wchar_t *string);

#endif	//DSTRING_H
