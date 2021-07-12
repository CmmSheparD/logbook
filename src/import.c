#include "import.h"

#include <stdlib.h>

#include <libxml/parser.h>

#include "log.c/src/log.h"

#include "dstring/bytes.h"
#include "dstring/convert.h"
#include "entry.h"

LogbookImportError_t scanEntry(const xmlNodePtr node, Entry_t **e)
{
	if (!xmlHasProp(node, (const xmlChar *)"title")){
		log_warn("Cannot find \"title\" property of entry.");
		return LIE_DOCUMENT_FORMAT_ERROR;
	}
	byte_str_t *buf = byte_createFromRaw(
		(char *)xmlGetProp(node, (const xmlChar *)"title"));
	log_debug("Entry [%p] title is \"%s\".", *e, buf->string);
	byte_toWideStr(buf, (*e)->title);
	if (!xmlIsBlankNode(node)) {
		log_debug("Current entry isn't blank.");
		byte_copyRaw(buf, (char *)xmlNodeGetContent(node));
		byte_toWideStr(buf, (*e)->text);
	}
	byte_free(buf);
	log_trace("Successfully read entry.");
	return LIE_OK;
}

LogbookImportError_t importLogbookXML(const char filename[], Logbook_t **lb)
{
	log_trace("Importing logbook from file.");
	if (!filename)
		return LIE_FILE_ERROR;
	LogbookImportError_t ret = LIE_OK;
	xmlDocPtr doc = xmlParseFile(filename);
	log_trace("Successfully read file.");

	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (!xmlHasProp(root, (const xmlChar *)"title")) {
		log_warn("Cannnot find \"title\" property of the document.");
		ret = LIE_DOCUMENT_FORMAT_ERROR;
	} else {
		log_trace("Found root \"title\" property.");
		byte_str_t *title = byte_createFromRaw(
			(char *)xmlGetProp(root, (const xmlChar *)"title"));
		log_debug("Document title is \"%s\".", title->string);
		byte_toWideStr(title, (*lb)->title);
		byte_free(title);

		xmlNodePtr children = root->children;
		for (size_t i = xmlChildElementCount(root);
			ret == LIE_OK && i > 0; --i) {
			log_debug("children = %p", children);
			log_debug("children->next = %p", children->next);
			Entry_t *entry = e_createEntry();
			if ((ret = scanEntry(children, &entry)) == LIE_OK) {
				lb_appendEntry(*lb, entry);
				children = children->next;
			} else {
				e_freeEntry(entry);
				break;
			}
		}
	}
	xmlFreeDoc(doc);
	log_trace("Read document with code %u.", ret);
	return ret;
}
