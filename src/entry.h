#pragma once
/*
 * Logbook entry type.
 */
#ifndef ENTRY_H
#define ENTRY_H

#include "DString/dstring.h"

typedef struct Entry {
	dstring_t *title, *text;
} Entry_t;

Entry_t *createEntry();

void freeEntry(Entry_t *e);

#endif	// ENTRY_H
