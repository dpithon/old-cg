.PHONY: all clean purge deps 

DEBUG=-O0 -g
CFLAGS+=-I/usr/local/include
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG)
LDFLAGS=-L./math -L./bpix -lmath -lbpix -lm
CC=gcc
LD=gcc
OBJS=pinhole.o raycaster.o sampler.o scene.o picture.o fatal.o renderer.o\
     surfaces.o

all: raycaster

clean:
	rm -rf *.o *.gch unit/*.o *.a raycaster *.pnm
	$(MAKE) -C math clean
	$(MAKE) -C bpix clean

purge: clean
	$(MAKE) -C math purge
	$(MAKE) -C bpix purge

deps:
	$(CC) -MM *.c >Makefile.deps
	$(MAKE) -C math deps


math/libmath.a: math/*.[ch]
	$(MAKE) -C math all

bpix/libbpix.a: bpix/*.[ch]
	$(MAKE) -C bpix all

raycaster: math/libmath.a bpix/libbpix.a $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $@

include Makefile.deps
