#pragma once
/*
 * Logbook entry type.
 */
#ifndef ENTRY_H
#define ENTRY_H

#include "DString/dstring.h"

typedef struct Entry {
	dstring_t *title, *text;
} entry_t;

entry_t *createEntry();

void freeEntry(entry_t *e);

#endif	// ENTRY_H
