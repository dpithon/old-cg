DEBUG=-O0 -g
CFLAGS+=-Wall -Wextra -Werror -std=c99 -pedantic -pipe $(DEBUG)
LDFLAGS=-lm

include Makefile.common
