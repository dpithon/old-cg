CFLAGS=-Wall -Wextra -std=c89 -pedantic -g3 -O0 -DGSEAL_ENABLE -pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15  

LDFLAGS= -pthread -lm -lgtk-3 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  

cg: gui.o backend.o main.o
	$(CC) $(LDFLAGS) $^ -o $@ 

gui.o: gui.c backend.h
backend.o: backend.c backend.h
draw.o: main.c gui.h backend.h

.PHONY: clean purge

clean:
	rm -f *.o

purge: clean
	rm cg
