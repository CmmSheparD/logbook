#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include "log.c/src/log.h"

#include "dstring/convert.h"
#include "dstring/bytes.h"
#include "dstring/wides.h"
#include "entry.h"
#include "export.h"
#include "import.h"
#include "logbook.h"

void setupLog(int level, bool quiet);

int getLine(wide_str_t *str, int len);

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
		wide_str_t *title = wide_create();
		getLine(title, 60);
		if (wide_isEmpty(title)) {
			wide_free(title);
			break;
		}
		Entry_t *e = e_createEntry();
		wide_appendStr(e->title, title);
		wide_create(title);
		getLine(e->text, 256);
		lb_appendEntry(lb, e);
	}
	byte_str_t *fname = byte_create();
	wide_toByteStr(lb->title, fname);
	byte_appendRaw(fname, ".xml");

	log_debug("File name is \"%s\".", fname->string);

	exportToXML(lb, fname->string);
	byte_free(fname);

	byte_str_t *title = byte_create();
	wide_toByteStr(lb->title, title);
	lb_freeLogbook(lb);

	lb = lb_createLogbook();
	byte_appendRaw(title, ".xml");
	importLogbookXML(title->string, &lb);
	byte_free(title);

	byte_str_t *text = byte_create();
	wide_toByteStr(lb->title, text);
	byte_appendRaw(text, ":");
	for (size_t i = 0; i < lb->entries->size; ++i) {
		byte_appendChar(text, '\n');
		byte_str_t *buf = byte_create();
		wide_toByteStr(lb->entries->array[i]->title, buf);
		byte_appendRaw(buf, ":\n\"");
		byte_appendStr(text, buf);
		buf->len = 0;
		buf->string[0] = '\0';
		wide_toByteStr(lb->entries->array[i]->text, buf);
		byte_appendRaw(buf, "\"\n");
		byte_appendStr(text, buf);
		byte_free(buf);
	}
	lb_freeLogbook(lb);
	addstr(text->string);
	byte_free(text);
	getch();
	endwin();
	return 0;
}

int getLine(wide_str_t *str, int len)
{
	char c;
	for (int i = 0; i < len && ((c = getch()) != '\n');) {
		if (c == '\n')
			break;
		addnstr(&c, 1);
		wchar_t	a;
		if (mbtowc(&a, &c, 1) != -1) {
			wide_appendChar(str, a);
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
