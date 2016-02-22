.PHONY: all clean purge deps 

DEBUG=-O0 -g
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG)
LDFLAGS=-L./bpix -lbpix -lm
CC=gcc
LD=gcc
OBJS=pinhole.o raycaster.o sampler.o scene.o picture.o fatal.o renderer.o\
     plane.o sphere.o vmath.o iomath.o painter.o ipoint.o plain-color.o\
     paraboloid.o

all: raycaster

clean:
	rm -rf *.o *.gch unit/*.o *.a raycaster *.pnm
	$(MAKE) -C bpix clean

purge: clean
	$(MAKE) -C bpix purge

deps:
	$(CC) -MM *.c >Makefile.deps


bpix/libbpix.a: bpix/*.[ch]
	$(MAKE) -C bpix all

raycaster: bpix/libbpix.a $(OBJS) 
	$(LD) $(OBJS) -o $@ $(LDFLAGS) 

include Makefile.deps
