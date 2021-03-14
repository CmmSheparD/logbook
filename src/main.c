#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DString/dstring.h"
#include "entry.h"
#include "logbook.h"

int getLine(dstring_t *str, int len);

int main()
{
	setlocale(LC_ALL, "en_US.utf-8");
	Logbook_t *lb = lb_createLogbook();
	getLine(lb->title, 60);
	while (!feof(stdin)) {
		Entry_t *e = e_createEntry();
		getLine(e->title, 60);
		getLine(e->text, 256);
		lb_appendEntry(lb, e);
	}
	char buf[lb->title->size * 4];
	wcstombs(buf, lb->title->raw_string, lb->title->size * 4);
	FILE *f = fopen(buf, "w");
	fwprintf(f, L"%ls", lb->title->raw_string);
	int n = lb_countEntries(lb);
	for (int i = 0; i < n; ++i) {
		fputwc(L'\n', f);
		Entry_t *e = lb_getEntry(lb, i);
		fwprintf(f, L"%ls\n%ls", e->title->raw_string,
			e->text->raw_string);
	}
	fclose(f);
	lb_freeLogbook(lb);
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
