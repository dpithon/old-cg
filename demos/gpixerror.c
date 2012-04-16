#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "gpix/gpix-error.h"

int main(int argc, char *argv[])
{
	int nr;

	if (argc < 2) {
		fprintf(stderr, "usage: %s gpix_error_nr\n", argv[0]);
		return 1;
	}

	errno = 0,
	nr = (int) strtol(argv[1], (char**) NULL, 10);

	if (errno) {
		fprintf(stderr, "invalid command line argument!\n");
		return 1;

	} else if (nr < 0 || nr > GPIX_ERR_MAX) {
		printf("no such error value (%d)\n", nr);

	} else if (! strncmp(GPIX_ERRSTR[nr], "", 1)) {
		printf("no such error value (%d)\n", nr);

	} else {
		printf("error #%03d: %s\n", nr, GPIX_ERRSTR[nr]);
	}

	return 0;
}