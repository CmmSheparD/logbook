#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.c/src/log.h"
#include <ncurses.h>

#include "DString/converters.h"
#include "DString/dbstring.h"
#include "DString/dstring.h"
#include "entry.h"
#include "logbook.h"
#include "export.h"

void setupLog(int level, bool quiet);

int getLine(dstring_t *str, int len);

int main()
{
	setlocale(LC_ALL, "en_US.utf-8");
	setupLog(LOG_TRACE, false);
	initscr();
	cbreak();
	noecho();
	Logbook_t *lb = lb_createLogbook();
	getLine(lb->title, 60);
	while (!feof(stdin)) {
		dstring_t *title = ds_createString();
		getLine(title, 60);
		if (ds_isEmpty(title)) {
			ds_freeString(title);
			break;
		}
		Entry_t *e = e_createEntry();
		ds_concatStrings(e->title, title);
		ds_freeString(title);
		getLine(e->text, 256);
		lb_appendEntry(lb, e);
	}
	dbstring_t *fname = dbs_createString();
	dcv_convertToBytes(lb->title, fname);
	dbs_appendString(fname, ".xml");

	log_debug("File name is \"%s\".", fname->raw_string);

	exportToXML(lb, fname->raw_string);
	dbs_freeString(fname);

	lb_freeLogbook(lb);
	endwin();
	return 0;
}

int getLine(dstring_t *str, int len)
{
	char c;
	for (int i = 0; i < len && ((c = getch()) != '\n');) {
		if (c == '\n')
			break;
		addnstr(&c, 1);
		wchar_t	a;
		if (mbtowc(&a, &c, 1) != -1) {
			ds_appendChar(str, a);
			refresh();
			++i;
		}
	}
	addch('\n');
	mbtowc(NULL, NULL, 0);
	return 0;
}

void setupLog(int level, bool quiet)
{
	log_set_level(level);
	log_set_quiet(quiet);
}
