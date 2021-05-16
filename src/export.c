#include "export.h"

#include <stdio.h>
#include <stdlib.h>

#include "log.c/src/log.h"

#include "DString/dstring.h"

int exportToText(const Logbook_t *lb, char filename[])
{
	log_trace("Exporting logbook to text file.");
	if (!lb || !lb->title || !lb->entries){
		log_debug("Some of related to exported logbook pointers are NULL.");
		return -1;
	}

	FILE *file = fopen(filename, "w");
	log_debug("File opened successfully.");
	
	fwprintf(file, L"%ls\n", lb->title->raw_string);
	int lblen = lb_countEntries(lb);
	for (int i = 0; i < lblen; ++i) {
		Entry_t *e = lb_getEntry(lb, i);
		fwprintf(file, L"\n%ls\n%ls\n", e->title->raw_string,
			e->text->raw_string);
	}
	log_debug("Finished exporting logbook to file.");
	fclose(file);
	log_trace("Successfully exported logbook to file.");
	return 0;
}
