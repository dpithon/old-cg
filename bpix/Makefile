.PHONY: all clean purge

CFLAGS=-Wall -Wextra -std=c89 -pedantic -g0 -O3

CAIRO_CFLAGS=$(CFLAGS) -pthread -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12  

GTK_CFLAGS=$(CFLAGS) -pthread -DGSEAL_ENABLE -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-3.0  

TARGETS=bpix-cairo.o bpix-core.o bpix-drawing.o bpix-error.o bpix-gtkwidget.o bpix-pnm.o

all: $(TARGETS)

bpix-pnm.o: bpix-pnm.c bpix-pnm.h bpix-core.h bpix-error.h
bpix-core.o: bpix-core.c bpix-core.h bpix-error.h
bpix-error.o: bpix-error.c
bpix-drawing.o: bpix-drawing.c bpix-core.h

bpix-cairo.o: bpix-cairo.c bpix-core.h bpix-error.h
	$(CC) -c $^ $(CAIRO_CFLAGS)

bpix-gtkwidget.o: bpix-gtkwidget.c bpix-core.h bpix-error.h bpix-cairo.h
	$(CC) -c $^ $(GTK_CFLAGS)

clean:
	rm -rf $(TARGETS) *.gch

purge: clean

