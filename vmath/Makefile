.PHONY: all clean purge test deps

OPTS=-DNDEBUG
OPTS=-DVSTAT
DEBUG=-O2 -g0
DEBUG=-O0 -g2
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
CC=gcc
LD=gcc
OBJS= vstat.o core.o io.o mstack.o

all: $(OBJS)

test: testing.o $(OBJS)
	$(LD) $^ -lm -o testing

clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -f testing

deps:
	$(CC) -MM *.c >Makefile.deps
 
include Makefile.deps
