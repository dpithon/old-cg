.PHONY: all clean purge test deps

OPTS=-DNDEBUG
OPTS=-DVSTAT
DEBUG=-O2 -g0
DEBUG=-O0 -g2
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
CC=gcc
LD=gcc
OBJS= stat.o core.o mstack.o iob.o settings.o
LDFLAGS=-L. -lvmath -lm

all: libvmath.a

libvmath.a: $(OBJS)
	ar -rs $@ $(OBJS)

test: testing.o
	$(LD) $^ $(LDFLAGS) -o testing

clean:
	rm -rf *.o *.gch unit/*.o *.a

purge: clean
	rm -f testing

deps:
	$(CC) -MM *.c >Makefile.deps
 
include Makefile.deps
