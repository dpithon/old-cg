.PHONY: all clean purge install

CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe
CC=gcc

OBJECTS=vmath.o

unit/vmath: unit/vmath.o vmath_nodbg.o
	$(CC) -o $@ $^ -lm

vmath.o: vmath.c vmath.h

vmath_nodbg.o: vmath.c vmath.h
	$(CC) -o $@ $(CFLAGS) -DNDEBUG -c $<

clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -rf $(TARGETS) *.pnm
