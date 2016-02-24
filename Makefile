.PHONY: all clean purge deps 

DEBUG=-O0 -g
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG) --coverage
LDFLAGS=-lm --coverage
CC=gcc
LD=gcc
OBJS=pinhole.o raycaster.o sampler.o scene.o picture.o fatal.o renderer.o\
     plane.o sphere.o vmath.o iomath.o painter.o ipoint.o plain-color.o\
     paraboloid.o cylinder.o pixmap.o

all: raycaster

clean:
	rm -rf *.o *.gch unit/*.o *.a raycaster *.pnm *.gcda *.gcno *.info

purge: clean

deps:
	$(CC) -MM *.c >Makefile.deps

raycaster: $(OBJS) 
	$(LD) $(OBJS) -o $@ $(LDFLAGS) 

include Makefile.deps
