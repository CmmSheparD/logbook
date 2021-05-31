#pragma once
/*
 * Functions to ease convertions between dynamic wide strings and
 * dynamic multibyte strings.
 */
#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "dbstring.h"
#include "dstring.h"

int dcv_convertToBytes(const dstring_t *src, dbstring_t *dest);

int dcv_convertToWide(const dbstring_t *src, dstring_t *dest);

#endif	// CONVERTERS_H
