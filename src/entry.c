#include "entry.h"

#include <stdlib.h>

Entry_t *e_createEntry()
{
	Entry_t *e = malloc(sizeof(*e));
	e->title = wide_create();
	e->text = wide_create();
	return e;
}

void e_freeEntry(Entry_t *e)
{
	wide_free(e->title);
	wide_free(e->text);
	free(e);
}
