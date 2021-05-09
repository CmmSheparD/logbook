#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.c/src/log.h"
#include <ncurses.h>

#include "DString/dstring.h"
#include "entry.h"
#include "logbook.h"
#include "export.h"

int getLine(dstring_t *str, int len);

int main()
{
	setlocale(LC_ALL, "en_US.utf-8");
	log_set_level(LOG_TRACE);
	initscr();
	cbreak();
	noecho();
	Logbook_t *lb = lb_createLogbook();
	getLine(lb->title, 60);
	while (!feof(stdin)) {
		dstring_t *title = ds_createString();
		getLine(title, 60);
		if (title->len == 0) {
			ds_freeString(title);
			break;
		}
		Entry_t *e = e_createEntry();
		ds_concatStrings(e->title, title);
		ds_freeString(title);
		getLine(e->text, 256);
		lb_appendEntry(lb, e);
	}
	exportToText(lb);
	lb_freeLogbook(lb);
	endwin();
	return 0;
}

int getLine(dstring_t *str, int len)
{
	char buf[5];
	buf[4] = '\0';
	*(int *)buf = 0;
	int j = 0;
	for (int i = 0; i < len && ((buf[j] = getch()) != '\n');) {
		if (buf[j] == '\n')
			break;
		++j;
		wchar_t	a;
		if (mbtowc(&a, buf + j - 1, 1) != -1) {
			ds_appendChar(str, a);
			addnstr(buf, j);
			refresh();
			j = 0;
			*(int *)buf = 0;
			++i;
		}
	}
	addch('\n');
	return 0;
}
