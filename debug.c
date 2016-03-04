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
void assert__is_mequal(const struct matrix *m1, const struct matrix *m2,
		      int line, char *file)
{
	if (!is_mequal(m1, m2)) {
		fprintf(stderr, HL "%s:%d assert_is_mequal(m1(%p), m2(%p)) "
			"failed!\n" NOHL, file, line, (void*)m1, (void*)m2);
		print_matrix("m1", m1);
		print_matrix("m2", m2);
		exit(1);
	}
}


void assert__is_vector(const struct coord *c, int line, char *file)
{
	if (!is_vector(c)) {
		fprintf(stderr, HL "%s:%d assert_is_vector(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_point(const struct coord *c, int line, char *file)
{
	if (!is_point(c)) {
		fprintf(stderr, HL "%s:%d assert_is_point(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}

void assert__is_not_vzero(const struct coord *c, int line, char *file)
{
	if (is_vzero(c)) {
		fprintf(stderr, HL "%s:%d assert_is_not_vzero(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_vunit(const struct coord *c, int line, char *file)
{
	if (!is_vunit(c)) {
		fprintf(stderr, HL "%s:%d assert_is_vunit(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_cartesian_coord_system(const struct coord *i,
				       const struct coord *j,
				       const struct coord *k,
				       int line, char *file)
{
	if (!is_cartesian_coord_system(i, j, k)) {
		fprintf(stderr, HL "%s:%d assert_is_cartesian_coord_system"
			"(i(%p), j(%p), k(%p)) failed!\n" NOHL, file, line,
			(void*)i, (void*)j, (void*)k);
		print_coord("i", i);
		print_coord("j", j);
		print_coord("k", k);
		exit(1);
	}
}

#endif
