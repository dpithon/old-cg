.PHONY: all clean purge install

CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe

OBJECTS=math3d.o transformation.o
TARGETS=libgeom.a test

all: $(TARGETS)

install: all
	mkdir /usr/include/geom
	install libgeom.a /usr/lib/
	install *.h /usr/include/geom/


libgeom.a: $(OBJECTS)
	rm -f $@
	ar -cvq $@ $^

test: test.o
	$(CC) -o $@ $^ -L/usr/local/lib -L. -lbpix -lgeom -lm

math3d.o: math3d.c math3d.h
test.o: test.c

clean:
	rm -rf *.o *.gch

purge: clean
	rm -rf $(TARGETS) *.pnm
