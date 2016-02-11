.PHONY: all clean

all: pinhole

clean:
	rm -f pinhole *.o

LDPATH=/usr/local/lib64

pinhole: pinhole.c
	gcc -o pinhole pinhole.c -lvmath -lm

