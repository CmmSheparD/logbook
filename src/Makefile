.POSIX:
EXE = logbook
CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic -DLOG_USE_COLOR -I/usr/include/libxml2
LDLIBS = -lm -lncursesw `xml2-config --libs`
OBJ = `find . -name "*.o"` 

all: $(EXE)
$(EXE): main.o logbook.o dstring/wides.o dstring/bytes.o dstring/convert.o entry.o export.o import.o log.c/src/log.o
	$(CC) $(LDFLAGS)-o $@ $(OBJ) $(LDLIBS)

log.c/src/log.o: log.c/src/log.c log.c/src/log.h
dstring/wides.o: dstring/wides.c dstring/wides.h
dstring/bytes.o: dstring/bytes.c dstring/bytes.h
dstring/convert.o: dstring/convert.c dstring/convert.h
main.o: main.c logbook.h entry.h dstring/wides.h dstring/bytes.h dstring/convert.h log.c/src/log.h
export.o: export.c export.h dstring/wides.h log.c/src/log.h
import.o: import.c import.h dstring/convert.h entry.h log.c/src/log.h
logbook.o: logbook.c logbook.h entry.h dstring/wides.h
entry.o: entry.c entry.h dstring/wides.h
clean:
	rm -f $(EXE) $(OBJ)
