#include "export.h"

#include <stdio.h>
#include <stdlib.h>

#include "log.c/src/log.h"

#include "DString/dstring.h"

int exportToText(const Logbook_t *lb)
{
	log_trace("Exporting logbook to text file.");
	if (!lb || !lb->title || !lb->entries){
		log_debug("Some of related to exported logbook pointers are NULL.");
		return -1;
	}

	dstring_t *fname = ds_createString();
	ds_concatStrings(fname, lb->title);
	ds_appendString(fname, L".txt");
	char *buf = malloc((fname->len + 1) * sizeof(*fname->raw_string));
	wcstombs(buf, fname->raw_string,
		(fname->len + 1) * sizeof(*fname->raw_string));
	ds_freeString(fname);
	log_debug("File name is \"%s\".", buf);

	FILE *file = fopen(buf, "w");
	log_debug("File opened successfully.");
	free(buf);
	
	fwprintf(file, L"%ls\n", lb->title->raw_string);
	int len = lb_countEntries(lb);
	for (int i = 0; i < len; ++i) {
		Entry_t *e = lb_getEntry(lb, i);
		fwprintf(file, L"\n%ls\n\n%ls\n", e->title->raw_string,
			e->text->raw_string);
	}
	log_debug("Finished exporting logbook to file.");
	fclose(file);
	log_trace("Successfully exported logbook to file.");
	return 0;
}
