#pragma once
/*
 * Exporting logbook to different formats.
 */
#ifndef EXPORT_H
#define EXPORT_H

#include "logbook.h"

/*
 * Exports given logbook in the following way: logbook title line, blank line
 * entry title, blank line, entry text, blank line, another entry title
 * ans so on. Example:
 * <logbook title>
 * 
 * <entry #1 title>
 * 
 * <text>
 * <text>
 * 
 * <text>
 * 
 * <entry #2 title>
 * ...
 */
int exportToText(const Logbook_t *lb);

#endif	// EXPORT_H
