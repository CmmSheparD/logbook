CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic -DLOG_USE_COLOR
LINK = -lncursesw `xml2-config --libs`
EXE = logbook

all: $(EXE)

$(EXE): main.o logbook.o dstring.o dbstring.o converters.o entry.o export.o log.o
	$(CC) -o $@ $^ $(LINK)

main.o: main.c logbook.h entry.h DString/dstring.h DString/dbstring.h DString/converters.h log.c/src/log.h
	$(CC) $(CFLAGS) $<

log.o: log.c/src/log.c log.c/src/log.h
	$(CC) $(CFLAGS) $<

export.o: export.c export.h DString/dstring.h log.c/src/log.h
	$(CC) $(CFLAGS) $< `xml2-config --cflags`

logbook.o: logbook.c logbook.h entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

entry.o: entry.c entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

dstring.o: DString/dstring.c DString/dstring.h
	$(CC) $(CFLAGS) $<

dbstring.o: DString/dbstring.c DString/dbstring.h
	$(CC) $(CFLAGS) $<

converters.o: DString/converters.c DString/converters.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE)
