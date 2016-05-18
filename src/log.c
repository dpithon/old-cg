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


int error(const char *msg, int ret)
{
	fprintf(stderr, RED "error: %s\n" NOHL, msg);
	return ret;
}


void warning(const char *msg)
{
	fprintf(stderr, YELLOW "warning: %s\n" NOHL, msg);
}


void info(const char *msg)
{
	fprintf(stderr, GREEN "info: %s\n" NOHL, msg);
}
