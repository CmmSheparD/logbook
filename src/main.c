#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DString/dstring.h"
#include "entry.h"

int getLine(dstring_t *str, int len);

int main()
{
	setlocale(LC_ALL, "en_US.utf-8");
	Entry_t *e = createEntry();
	wprintf(L"Enter title:\t");
	getLine(e->title, 64);
	wprintf(L"Enter text:\t");
	getLine(e->text, 0);
	char buf[e->title->size * 4];
	wcstombs(buf, e->title->string, e->title->size * 4);
	FILE *f = fopen(buf, "w");
	fwprintf(f, L"Title: %ls\nText: %ls\n", e->title->string, e->text->string);
	fclose(f);
	freeEntry(e);
	return 0;
}

int getLine(dstring_t *str, int len)
{
	bool tilend = len == 0;
	wchar_t c;
	for (int i = 0; (tilend || i < len) && ((c = getwchar()) != EOF); ++i) {
		if (!tilend && c == '\n')
			break;
		ds_appendChar(str, c);
	}
	return 0;
}
