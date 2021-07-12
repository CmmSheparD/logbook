#pragma once
/*
 * Logbook entry type.
 */
#ifndef ENTRY_H
#define ENTRY_H

#include "dstring/wides.h"

typedef struct Entry {
	wide_str_t *title;
	wide_str_t *text;
} Entry_t;

Entry_t *e_createEntry();
void e_freeEntry(Entry_t *e);

#endif	// ENTRY_H
