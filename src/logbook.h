#pragma once
/*
 * Logbook type.
 */
#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <stdbool.h>

#include "DString/dstring.h"
#include "entry.h"

/*
 * Dynamic array of pointers to logbook entries.
 */
struct _Entry_DA {
	size_t size;
	size_t max;
	Entry_t **array;
};

typedef struct Logbook {
	dstring_t *title;
	struct _Entry_DA *entries;
} Logbook_t;

Logbook_t *lb_createLogbook();
void lb_freeLogbook(Logbook_t *lb);

bool lb_isEmpty(const Logbook_t *lb);
int lb_countEntries(const Logbook_t *lb);

int lb_appendEntry(const Logbook_t *lb, Entry_t *entry);

/*
 * Returns pointer that is ind-th in the array.
 */
Entry_t *lb_getEntry(const Logbook_t *lb, size_t ind);
Entry_t *lb_getLastEntry(const Logbook_t *lb);

#endif	// LOGBOOK_H
