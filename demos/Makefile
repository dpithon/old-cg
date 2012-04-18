.PHONY: all clean purge

CFLAGS=-Wall -Wextra -std=c89 -pedantic -g0 -O3 -I..

GTK_CFLAGS=$(CFLAGS) -pthread -DGSEAL_ENABLE -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-3.0  

GTK_LDFLAGS=-pthread -lgtk-3 -lgdk-3 -latk-1.0 -lcairo-gobject -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  

CC=gcc

TARGETS=gpixerror lines lines_gui gfract

all: $(TARGETS)

gpixerror: gpixerror.o ../gpix/gpix-error.o
	$(CC) -o $@ $^

lines: lines.o  ../gpix/gpix-core.o ../gpix/gpix-error.o \
	 ../gpix/gpix-drawing.o ../gpix/gpix-pnm.o
	$(CC) -o $@ $^ -lm

lines_gui:  lines_gui.o ../gpix/gpix-core.o \
	 ../gpix/gpix-error.o ../gpix/gpix-drawing.o \
	 ../gpix/gpix-gtkwidget.o ../gpix/gpix-cairo.o
	$(CC) -o $@ $^ $(GTK_LDFLAGS) -lm

gfract: gfract.o  ../gpix/gpix-core.o ../gpix/gpix-error.o \
	 ../gpix/gpix-drawing.o ../gpix/gpix-pnm.o
	$(CC) -o $@ $^ -lm

gpixerror.o: gpixerror.c ../gpix/gpix-error.h
lines.o: lines.c ../gpix/gpix.h ../gpix/gpix-core.h ../gpix/gpix-error.h \
	 ../gpix/gpix-drawing.h ../gpix/gpix-pnm.h

lines_gui.o: lines_gui.c ../gpix/gpix.h ../gpix/gpix-core.h \
	 ../gpix/gpix-error.h ../gpix/gpix-drawing.h ../gpix/gpix-pnm.h \
	 ../gpix/gpix-gtkwidget.h ../gpix/gpix.h
	$(CC) -c $< $(GTK_CFLAGS)

clean:
	rm -rf *.o *.gch

purge: clean
	rm -rf $(TARGETS) *.pnm
