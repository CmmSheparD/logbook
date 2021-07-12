CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic -DLOG_USE_COLOR
LINK = -lm -lncursesw `xml2-config --libs`
EXE = logbook

all: $(EXE)

$(EXE): main.o logbook.o wides.o bytes.o convert.o entry.o export.o import.o log.o
	$(CC) -o $@ $^ $(LINK)

main.o: main.c logbook.h entry.h dstring/wides.h dstring/bytes.h dstring/convert.h log.c/src/log.h
	$(CC) $(CFLAGS) $<

log.o: log.c/src/log.c log.c/src/log.h
	$(CC) $(CFLAGS) $<

export.o: export.c export.h dstring/wides.h log.c/src/log.h
	$(CC) $(CFLAGS) $< `xml2-config --cflags`

import.o: import.c import.h dstring/convert.h entry.h log.c/src/log.h
	$(CC) $(CFLAGS) $< `xml2-config --cflags`

logbook.o: logbook.c logbook.h entry.h dstring/wides.h
	$(CC) $(CFLAGS) $<

entry.o: entry.c entry.h dstring/wides.h
	$(CC) $(CFLAGS) $<

wides.o: dstring/wides.c dstring/wides.h
	$(CC) $(CFLAGS) $<

bytes.o: dstring/bytes.c dstring/bytes.h
	$(CC) $(CFLAGS) $<

convert.o: dstring/convert.c dstring/convert.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE)
