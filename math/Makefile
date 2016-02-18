.PHONY: all clean purge test deps install

OPTS=-DNDEBUG
DEBUG=-O0 -g2
DEBUG=-O0 -g
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
CC=gcc
LD=gcc
OBJS=core.o mstack.o iob.o settings.o misc.o
LDFLAGS=-L. -lmath -lm

all: libmath.a

libmath.a: $(OBJS)
	ar -rs $@ $(OBJS)

clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -f libmath.a

deps:
	$(CC) -MM *.c >Makefile.deps

include Makefile.deps
