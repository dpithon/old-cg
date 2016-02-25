.PHONY: all clean purge deps

CC=gcc
LD=gcc

DEBUG=-O0 -g
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG)
LDFLAGS=-lm
OBJS=pinhole.o raycaster.o sampler.o scene.o log.o renderer.o\
     plane.o sphere.o vmath.o iomath.o painter.o ipoint.o plain-color.o\
     paraboloid.o cylinder.o pixmap.o

all: raycaster

clean:
	rm -rf *.o *.gch unit/*.o *.a raycaster *.pnm *.gcda *.gcno *.info

purge: clean
	rm -rf html

deps:
	$(CC) -MM *.c >Makefile.deps

raycaster: $(OBJS) 
	$(LD) $(OBJS) -o $@ $(LDFLAGS) 

include Makefile.deps
