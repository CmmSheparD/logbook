#include "entry.h"

#include <stdlib.h>

Entry_t *e_createEntry()
{
	Entry_t *e = malloc(sizeof(*e));
	e->title = ds_createString();
	e->text = ds_createString();
	return e;
}

void e_freeEntry(Entry_t *e)
{
	ds_freeString(e->title);
	ds_freeString(e->text);
	free(e);
}
