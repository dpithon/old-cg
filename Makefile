.PHONY: all clean purge deps 

OPTS=-DNDEBUG
DEBUG=-O0 -g2
CFLAGS+=-I/usr/local/include
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) $(OPTS)
LDFLAGS=-L./math -L./bpix -lmath -lbpix -lm
CC=gcc
LD=gcc
OBJS=pinhole.o raycaster.o sampler.o scene.o

all: raycaster

clean:
	rm -rf *.o *.gch unit/*.o *.a
	$(MAKE) -C math clean
	$(MAKE) -C bpix clean

purge: clean
	rm -f raycaster *.pnm
	$(MAKE) -C math purge
	$(MAKE) -C bpix purge

deps:
	$(CC) -MM *.c >Makefile.deps
	$(MAKE) -C math deps
	$(MAKE) -C bpix deps


math/libmath.a: math/*.[ch]
	$(MAKE) -C math all

bpix/libbpix.a: bpix/*.[ch]
	$(MAKE) -C bpix all

raycaster: $(OBJS) math/libmath.a bpix/libbpix.a
	$(LD) $(LDFLAGS) $(OBJS) -o $@

include Makefile.deps
