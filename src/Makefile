CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic -DLOG_USE_COLOR
LINK = -lncurses
EXE = logbook

all: $(EXE)

$(EXE): main.o logbook.o dstring.o entry.o export.o log.o
	$(CC) -o $@ $^ $(LINK)

main.o: main.c logbook.h entry.h DString/dstring.h log.c/src/log.h
	$(CC) $(CFLAGS) $<

log.o: log.c/src/log.c log.c/src/log.h
	$(CC) $(CFLAGS) $<

export.o: export.c export.h DString/dstring.h log.c/src/log.h
	$(CC) $(CFLAGS) $<

logbook.o: logbook.c logbook.h entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

entry.o: entry.c entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

dstring.o: DString/dstring.c DString/dstring.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE)
