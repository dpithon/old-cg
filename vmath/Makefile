.PHONY: all clean purge test deps install

OPTS=-DNDEBUG
DEBUG=-O2 -g0
DEBUG=-O0 -g2
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
CC=gcc
LD=gcc
OBJS=core.o mstack.o iob.o settings.o misc.o
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

install: all
	mkdir -p /usr/local/include/rt
	cp *.h /usr/local/include/rt
	cp *.a /usr/local/lib

include Makefile.deps
