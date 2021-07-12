#include "export.h"

#include <stdlib.h>

#include <libxml/tree.h>

#include "log.c/src/log.h"

#include "dstring/bytes.h"
#include "dstring/convert.h"

int exportToText(const Logbook_t *lb, const char filename[])
{
	log_trace("Exporting logbook to text file.");
	if (!lb || !lb->title || !lb->entries) {
		log_debug("Some of related to exported logbook pointers are NULL.");
		return -1;
	}

	FILE *file = fopen(filename, "w");
	log_debug("File opened successfully.");
	
	fwprintf(file, L"%ls\n", lb->title->string);
	int lblen = lb_countEntries(lb);
	for (int i = 0; i < lblen; ++i) {
		Entry_t *e = lb_getEntry(lb, i);
		fwprintf(file, L"\n%ls\n%ls\n", e->title->string,
			e->text->string);
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
	byte_str_t *str = byte_create();
	wide_toByteStr(entry->title, str);
	xmlNewProp(e, (const xmlChar *)"title",
		(const xmlChar *)str->string);

	wide_toByteStr(entry->text, str);
	xmlNodeAddContent(e, (const xmlChar *)str->string);
	byte_free(str);

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
	byte_str_t *title = byte_create();
	wide_toByteStr(lb->title, title);
	xmlNewProp(root, (const xmlChar *)"title",
		(const xmlChar *)title->string);
	log_debug("The \"title\" was set to \"%s\".", title->string);
	byte_free(title);

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
