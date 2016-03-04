#include <stdio.h>
#include <stdlib.h>
#include "vmath.h"

#define HL   "\033[33m"
#define NOHL "\033[0m"


void fatal(const char *msg)
{
	fprintf(stderr, HL "FATAL: %s\n" NOHL, msg);
	exit(1);
}


void warning(const char *msg)
{
	fprintf(stderr, HL "Warning: %s\n" NOHL, msg);
}


#ifndef NDEBUG
void assert_is_mequal(const struct matrix *m1, const struct matrix *m2)
{
	if (!is_mequal(m1, m2)) {
		fprintf(stderr, HL "assert_is_mequal(m1(%p), m2(%p)) "
			"failed!\n" NOHL, (void*)m1, (void*)m2);
		print_matrix("m1", m1);
		print_matrix("m2", m2);
		exit(1);
	}
}
#endif
