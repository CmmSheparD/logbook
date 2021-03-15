#include "export.h"

#include <stdio.h>
#include <stdlib.h>

#include "DString/dstring.h"

int exportToText(const Logbook_t *lb)
{
	if (!lb || !lb->title || !lb->entries) return -1;

	dstring_t *fname = ds_createString();
	ds_concatStrings(fname, lb->title);
	ds_appendString(fname, L".txt");
	char *buf = malloc(fname->size * sizeof(*fname->raw_string));
	wcstombs(buf, fname->raw_string,
		fname->size * sizeof(*fname->raw_string));
	FILE *file = fopen(buf, "w");
	ds_freeString(fname);
	fname = NULL;
	free(buf);
	buf = NULL;
	
	fwprintf(file, L"%ls\n", lb->title->raw_string);
	int len = lb_countEntries(lb);
	for (int i = 0; i < len; ++i) {
		Entry_t *e = lb_getEntry(lb, i);
		fwprintf(file, L"\n%ls\n\n%ls\n", e->title->raw_string,
			e->text->raw_string);
	}
	fclose(file);
	return 0;
}
