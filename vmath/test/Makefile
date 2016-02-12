.PHONY: all clean purge

all: pinhole

clean:
	rm -f pinhole *.o

purge: clean

CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lvmath -lm
CC=gcc

TARGETS=pinhole

all: $(TARGETS)

pinhole: pinhole.o
	gcc $^ $(LDFLAGS) -o $@
