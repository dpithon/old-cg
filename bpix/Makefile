.PHONY: all clean purge install

CFLAGS=-Wall -Wextra -std=c99 -pedantic -g0 -O3 -pipe
OBJECTS=bpix-core.o bpix-drawing.o bpix-error.o bpix-pnm.o
CC=gcc
LD=gcc

all: libbpix.a

install: all
	mkdir -p /usr/local/include/rt
	cp libbpix.a /usr/local/lib/
	cp *.h /usr/local/include/rt/


libbpix.a: $(OBJECTS)
	rm -f $@
	ar -cvq $@ $^

bpix-pnm.o: bpix-pnm.c bpix-pnm.h bpix-core.h bpix-error.h
bpix-core.o: bpix-core.c bpix-core.h bpix-error.h
bpix-error.o: bpix-error.c
bpix-drawing.o: bpix-drawing.c bpix-core.h

clean:
	rm -rf $(OBJECTS) *.gch

purge: clean
	rm libbpix.a

