#include "export.h"

#include <stdlib.h>

#include <libxml/tree.h>

#include "log.c/src/log.h"

#include "DString/dstring.h"

int exportToText(const Logbook_t *lb, const char filename[])
{
	log_trace("Exporting logbook to text file.");
	if (!lb || !lb->title || !lb->entries) {
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

void appendEntryToXML(xmlDocPtr doc, const Entry_t *entry)
{
	xmlNodePtr e = xmlNewDocNode(
		doc,
		NULL,
		(const xmlChar *)"Entry",
		NULL);
	size_t dlen = ds_multibyteLength(entry->title);
	char *str = malloc(dlen);
	ds_dumpToChars(entry->title, str, dlen);
	xmlNewProp(e, (const xmlChar *)"title", (const xmlChar *)str);

	dlen = ds_multibyteLength(entry->text);
	str = realloc(str, dlen);
	ds_dumpToChars(entry->text, str, dlen);
	xmlNodeAddContent(e, (const xmlChar *)str);
	free(str);

	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlAddChild(root, e);
}

int exportToXML(const Logbook_t *lb, const char filename[])
{
	log_trace("Exporting logbook to XML file.");
	if (!lb || !lb->title || !lb->entries || !filename)
		return -1;
	xmlDocPtr doc = xmlNewDoc((const xmlChar *)"1.0");
	xmlNodePtr root = xmlNewDocNode(
		doc,
		NULL,
		(const xmlChar *)"Logbook",
		NULL);
	xmlDocSetRootElement(doc, root);

	xmlNewProp(root, (const xmlChar *)"doc_version",
		(const xmlChar *)"0.1");
	char title[ds_multibyteLength(lb->title)];
	ds_dumpToChars(lb->title, title, ds_multibyteLength(lb->title));
	xmlNewProp(root, (const xmlChar *)"title", (const xmlChar *)title);

	for (int i = 0; i < lb_countEntries(lb); ++i) {
		appendEntryToXML(doc, lb_getEntry(lb, i));
	}

	xmlSaveFileEnc(filename, doc, "utf-8");
	xmlFreeDoc(doc);
	log_trace("Successfully exported logbook to XML file.");
	return 0;
}
