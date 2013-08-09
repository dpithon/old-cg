.PHONY: all clean purge install

CFLAGS+=-Wall -Wextra -std=c99 -pedantic -pipe
CC=gcc
LD=gcc

pptst: pptst.o vmath.o pprint.o
	$(LD) -o $@ -lm $^

vmath.o: vmath.c vmath.h
pprint.o: pprint.c pprint.h
pptst.o: pptst.c


clean:
	rm -rf *.o *.gch unit/*.o

purge: clean
	rm -rf $(TARGETS) *.pnm
