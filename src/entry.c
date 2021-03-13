#include <stdlib.h>

#include "entry.h"

Entry_t *createEntry()
{
	Entry_t *e = malloc(sizeof(*e));
	e->title = ds_createString();
	e->text = ds_createString();
	return e;
}

void freeEntry(Entry_t *e)
{
	ds_freeString(e->title);
	ds_freeString(e->text);
	free(e);
}
