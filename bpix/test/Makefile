.PHONY: all clean purge

CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lbpix -lm

CC=gcc

TARGETS=bpixerror lines gfract gfract2 redbox

all: $(TARGETS)

bpixerror: bpixerror.o
	gcc $^ $(LDFLAGS) -o $@

redbox: redbox.o
	gcc $^ $(LDFLAGS) -o $@

lines: lines.o
	gcc $^ $(LDFLAGS) -o $@

gfract: gfract.o
	gcc $^ $(LDFLAGS) -o $@

gfract2: gfract2.o
	gcc $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.gch

purge: clean
	rm -rf $(TARGETS) *.pnm
