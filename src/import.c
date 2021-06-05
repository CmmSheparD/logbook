#include "import.h"

#include <stdlib.h>

#include <libxml/parser.h>

#include "log.c/src/log.h"

#include "DString/converters.h"
#include "entry.h"

LogbookImportError_t scanEntry(const xmlNodePtr node, Entry_t **e)
{
	if (!xmlHasProp(node, (const xmlChar *)"title")){
		log_warn("Cannot find \"title\" property of entry.");
		return LIE_DOCUMENT_FORMAT_ERROR;
	}
	dbstring_t *buf = dbs_createString();
	dbs_appendString(buf,
		(char *)xmlGetProp(node, (const xmlChar *)"title"));
	log_debug("Entry [%p] title is \"%s\".", *e, buf->raw_string);
	dcv_convertToWide(buf, (*e)->title);
	if (!xmlIsBlankNode(node)) {
		log_debug("Current entry isn't blank.");
		buf->len = 0;
		buf->raw_string[0] = '\0';
		dbs_appendString(buf, (char *)xmlNodeGetContent(node));
		dcv_convertToWide(buf, (*e)->text);
	}
	dbs_freeString(buf);
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
		dbstring_t *title = dbs_createString();
		dbs_appendString(title,
			(char *)xmlGetProp(root, (const xmlChar *)"title"));
		log_debug("Document title is \"%s\".", title->raw_string);
		dcv_convertToWide(title, (*lb)->title);
		dbs_freeString(title);

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
