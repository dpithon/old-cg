.PHONY: all clean purge

OPTS=-DCOUNTERS
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe -O0 -g2 $(OPTS)
CC=gcc
LD=gcc
OBJS=../core.o ../io.o ../mstack.o rotation.o
TARGETS=rotation

all: $(TARGETS)

rotation: rotation.o
	$(LD) $(OBJS) -lm -o $@

clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -rf $(TARGETS)

rotation.o: rotation.c
