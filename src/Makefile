CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic
LINK = -lncurses
EXE = logbook

all: $(EXE)

$(EXE): main.o dstring.o entry.o
	$(CC) -o $@ $^ $(LINK)

main.o: main.c entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

entry.o: entry.c entry.h DString/dstring.h
	$(CC) $(CFLAGS) $<

dstring.o: DString/dstring.c DString/dstring.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE)
