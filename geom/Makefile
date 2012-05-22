.PHONY: all clean purge install

CFLAGS=-Wall -Wextra -std=c99 -pedantic -g3 -O0 -pipe

OBJECTS=math3d.o transformation.o

all: libgeom.a

install: all
	mkdir /usr/include/geom
	install libgeom.a /usr/lib/
	install *.h /usr/include/geom/


libgeom.a: $(OBJECTS)
	ar -cvq $@ $^

math3d.o: math3d.c math3d.h

clean:
	rm -rf *.o *.gch

purge: clean
	rm -rf lib*a
