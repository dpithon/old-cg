#include <stdio.h>
#include <stdlib.h>

void fatal(const char *msg)
{
	fprintf(stderr, "FATAL: %s\n", msg);
	exit(1);
}


void warning(const char *msg)
{
	fprintf(stderr, "Warning: %s\n", msg);
}
