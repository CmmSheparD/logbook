#pragma once
/*
 * Logbook import functions.
 */
#ifndef IMPORT_H
#define IMPORT_H

#include "logbook.h"

typedef enum LogbookImportError {
	LIE_OK,
	LIE_FILE_ERROR,
	LIE_DOCUMENT_FORMAT_ERROR
} LogbookImportError_t;

LogbookImportError_t importLogbookXML(const char filename[], Logbook_t **lb);

#endif	// IMPORT_H
