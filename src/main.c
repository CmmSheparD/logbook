#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DString/dstring.h"
#include "entry.h"
#include "logbook.h"
#include "export.h"

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
	exportToText(lb);
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
