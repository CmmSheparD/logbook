#include "export.h"

#include <stdlib.h>

#include <libxml/tree.h>

#include "log.c/src/log.h"

#include "DString/converters.h"
#include "DString/dbstring.h"
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
	dbstring_t *str = dbs_createString();
	dcv_convertToBytes(entry->title, str);
	xmlNewProp(e, (const xmlChar *)"title",
		(const xmlChar *)str->raw_string);

	dcv_convertToBytes(entry->text, str);
	xmlNodeAddContent(e, (const xmlChar *)str->raw_string);
	dbs_freeString(str);

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

	log_debug("Putting title into xml.");
	dbstring_t *title = dbs_createString();
	dcv_convertToBytes(lb->title, title);
	xmlNewProp(root, (const xmlChar *)"title",
		(const xmlChar *)title->raw_string);
	log_debug("The \"title\" was set to \"%s\".", title->raw_string);
	dbs_freeString(title);

	for (int i = 0; i < lb_countEntries(lb); ++i) {
		appendEntryToXML(doc, lb_getEntry(lb, i));
	}
	log_debug("Saving file.");
	xmlSaveFileEnc(filename, doc, "utf-8");
	log_debug("File saved.");

	xmlFreeDoc(doc);
	log_trace("Successfully exported logbook to XML file.");
	return 0;
}
