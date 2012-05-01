.PHONY: all clean purge install

CFLAGS=-Wall -Wextra -std=c99 -pedantic -g0 -O3 -pipe

CAIRO_CFLAGS=$(CFLAGS) $(shell pkg-config --cflags cairo)
GTK_CFLAGS=$(CFLAGS) $(shell pkg-config --cflags gtk+-3.0)

OBJECTS=bpix-cairo.o bpix-core.o bpix-drawing.o bpix-error.o bpix-gtk.o bpix-pnm.o

all: libbpix.a

install: all
	mkdir /usr/include/bpix
	install libbpix.a /usr/lib/
	install *.h /usr/include/bpix/


libbpix.a: $(OBJECTS)
	ar -cvq $@ $^

bpix-pnm.o: bpix-pnm.c bpix-pnm.h bpix-core.h bpix-error.h
bpix-core.o: bpix-core.c bpix-core.h bpix-error.h
bpix-error.o: bpix-error.c
bpix-drawing.o: bpix-drawing.c bpix-core.h

bpix-cairo.o: bpix-cairo.c bpix-core.h bpix-error.h
	$(CC) -c $^ $(CAIRO_CFLAGS)

bpix-gtk.o: bpix-gtk.c bpix-core.h bpix-error.h bpix-cairo.h
	$(CC) -c $< $(GTK_CFLAGS)

clean:
	rm -rf $(OBJECTS) libbpix.a *.gch

purge: clean

