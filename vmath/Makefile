.PHONY: all clean purge test

OPTS=-DVSTAT
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe -O0 -g2 $(OPTS)
CC=gcc
LD=gcc
OBJS= vstat.o core.o io.o mstack.o

all: $(OBJS)

test: testing.o $(OBJS)
	$(LD) $^ -lm -o testing

clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -f testing

core.o: core.c core.h
io.o: io.c io.h
mstack.o: mstack.c mstack.h mstack.p
stat.o: stat.c stat.h stat.p
testing.o: testing.c
