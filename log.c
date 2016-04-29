#include <stdio.h>
#include <stdlib.h>
#include "ansicodes.h"


#ifndef NDEBUG
void debug_(const char *msg)
{
	fprintf(stderr, BLUE "debug: %s\n" NOHL, msg);
}
#endif


void fatal(const char *msg)
{
	fprintf(stderr, RED "FATAL: %s\n" NOHL, msg);
	exit(1);
}


void warning(const char *msg)
{
	fprintf(stderr, YELLOW "Warning: %s\n" NOHL, msg);
}


int error(const char *msg, int ret)
{
	fprintf(stderr, RED "Error: %s\n" NOHL, msg);
	return ret;
}
