.PHONY: all clean

all: pinhole

clean:
	rm -f pinhole *.o

CFLAGS=-I/usr/local/include
LDPATH=/usr/local/lib
LDFLAGS=-L/usr/local/lib -lvmath -lm
CC=gcc

pinhole: pinhole.c
