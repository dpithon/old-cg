.PHONY: all clean purge

CFLAGS=-Wall -Wextra -std=c89 -pedantic -g0 -O3 -I..

GTK_CFLAGS=$(CFLAGS) -pthread -DGSEAL_ENABLE -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-3.0  

GTK_LDFLAGS=-pthread -lgtk-3 -lgdk-3 -latk-1.0 -lcairo-gobject -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  

CC=gcc

TARGETS=bpixerror lines lines_gui gfract gfract2 redbox gfract2_gui

all: $(TARGETS)

bpixerror: bpixerror.o ../bpix/bpix-error.o
	$(CC) -o $@ $^

redbox: redbox.o
	$(CC) -o $@ $^ -lm -L../bpix -lbpix

lines: lines.o
	$(CC) -o $@ $^ -lm -L../bpix -lbpix

lines_gui: lines_gui.o
	$(CC) -o $@ $^ -L../bpix -lbpix $(GTK_LDFLAGS) -lm

gfract2_gui: gfract2_gui.o
	$(CC) -o $@ $^ -L../bpix -lbpix $(GTK_LDFLAGS) -lm

gfract: gfract.o
	$(CC) -o $@ $^ -lm -L../bpix -lbpix

gfract2: gfract2.o
	$(CC) -o $@ $^ -lm -L../bpix -lbpix

bpixerror.o: bpixerror.c ../bpix/bpix-error.h
lines.o: lines.c ../bpix/bpix.h ../bpix/bpix-core.h ../bpix/bpix-error.h \
	 ../bpix/bpix-drawing.h ../bpix/bpix-pnm.h

lines_gui.o: lines_gui.c ../bpix/bpix.h ../bpix/bpix-core.h \
	 ../bpix/bpix-error.h ../bpix/bpix-drawing.h ../bpix/bpix-pnm.h \
	 ../bpix/bpix-gtk.h ../bpix/bpix.h
	$(CC) -c $< $(GTK_CFLAGS)

gfract2_gui.o: gfract2_gui.c ../bpix/bpix.h ../bpix/bpix-core.h \
	 ../bpix/bpix-error.h ../bpix/bpix-drawing.h ../bpix/bpix-pnm.h \
	 ../bpix/bpix-gtk.h ../bpix/bpix.h
	$(CC) -c $< $(GTK_CFLAGS)
clean:
	rm -rf *.o *.gch

purge: clean
	rm -rf $(TARGETS) *.pnm
