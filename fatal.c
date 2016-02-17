#include <stdio.h>
#include <stdlib.h>

void fatal(const char *msg)
{
	fprintf(stderr, "*** %s ***\n", msg);
	exit(1);
}
