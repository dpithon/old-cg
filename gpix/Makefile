.PHONY: all clean purge

CFLAGS=-Wall -Wextra -std=c89 -pedantic -g0 -O3

CAIRO_CFLAGS=$(CFLAGS) -pthread -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12  

GTK_CFLAGS=$(CFLAGS) -pthread -DGSEAL_ENABLE -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-3.0  

TARGETS=gpix-cairo.o gpix-core.o gpix-drawing.o gpix-error.o gpix-gtkwidget.o gpix-pnm.o

all: $(TARGETS)

gpix-pnm.o: gpix-pnm.c gpix-pnm.h gpix-core.h gpix-error.h
gpix-core.o: gpix-core.c gpix-core.h gpix-error.h
gpix-error.o: gpix-error.c
gpix-drawing.o: gpix-drawing.c gpix-core.h

gpix-cairo.o: gpix-cairo.c gpix-core.h gpix-error.h
	$(CC) -c $^ $(CAIRO_CFLAGS)

gpix-gtkwidget.o: gpix-gtkwidget.c gpix-core.h gpix-error.h gpix-cairo.h
	$(CC) -c $^ $(GTK_CFLAGS)

clean:
	rm -rf $(TARGETS) *.gch

purge: clean

