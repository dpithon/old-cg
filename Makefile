.PHONY: all clean purge deps

OPTS=-DNDEBUG
DEBUG=-O0 -g2
CFLAGS+=-I/usr/local/include
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
LDFLAGS=-L/usr/local/lib -lvmath -lbpix -lm
CC=gcc
LD=gcc
OBJS=pinhole.o raycaster.o

all: $(OBJS)

clean:
	rm -rf *.o *.gch unit/*.o *.a

purge: clean
	rm -f testing

deps:
	$(CC) -MM *.c >Makefile.deps

raycaster: all
	$(LD) $(LDFLAGS) $(OBJS) -o $@
include Makefile.deps
