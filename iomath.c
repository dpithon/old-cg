#include <stdio.h>
#include "vmath.h"

void print_matrix(const char *pfx, const struct matrix *m)
{
	if (pfx)
		printf("%s\n", pfx);
	printf("---------------------------\n");

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			printf("%15.11f ", m->cell[r][c]);
		}
		printf("\n");
	}
}
