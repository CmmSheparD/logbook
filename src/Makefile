CC = gcc
CFLAGS = -c -Wall -Wextra -Wpedantic
LINK = -lncurses
EXE = scrollkeeper

all: $(EXE)

$(EXE): main.o
	$(CC) -o $@ $^ $(LINK)

main.o: main.c
	$(CC) $(CFLAGS) $<

clean:
	rm *.o $(EXE)
