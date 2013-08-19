.PHONY: all clean purge test

OPTS=-DCOUNTERS
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe -O0 -g2 $(OPTS)
CC=gcc
LD=gcc
OBJS=core.o io.o mstack.o

all: $(OBJS)

test: all
	$(MAKE) -C test

clean:
	rm -rf *.o *.gch unit/*.o
	$(MAKE) -C test clean

purge: clean
	$(MAKE) -C test purge

core.o: core.c core.h
io.o: io.c io.h
mstack.o: mstack.c mstack.h
