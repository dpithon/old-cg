.PHONY: all clean purge

CFLAGS=-Wall -Wextra -std=c99 -pedantic -g0 -O3 -pipe -I..
GTK_CFLAGS=$(CFLAGS) $(shell pkg-config --cflags gtk+-3.0)
GTK_LDFLAGS=$(shell pkg-config --libs gtk+-3.0)

CC=gcc

TARGETS=bpixerror lines lines_gui gfract gfract2 redbox gfract2_gui math3d_test

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
	$(CC) -o $@ $^ -L../bpix -lbpix -lm

gfract2: gfract2.o
	$(CC) -o $@ $^ -L../bpix -lbpix -lm

math3d_test: math3d_test.o
	$(CC) -o $@ $^ -L../bpix -lbpix -L../geom -lgeom -lm

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
