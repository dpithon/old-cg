#include "gpix-error.h"

const char *GPIX_ERRSTR[] = {
	/*     0 */	"no error",
	/*     1 */	"gpix already initialized",
	/*     2 */	"wrong width and/or height values",
	/*     3 */	"failed to malloc() pixmap buffer",
	/*     4 */	"surface already freed",
	/*     5 */	"uninitialized gpix",
	/*     6 */	"out of bound coordinates",
	/*  7-19 */	"", "", "", "", "", "", "", "", "", "", "", "", "",
	/*    20 */	"failed to create cairo surface from gpix",
	/*    21 */	"failed to initialize gpix from cairo surface",
	/* 22-29 */	"", "", "", "", "", "", "", "",
	/* 30-39 */	"i/o error", "", "", "", "", "", "", "", "", "",
	/*    40 */	"Gtk error"
};


