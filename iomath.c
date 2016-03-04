#include <stdio.h>
#include "vmath.h"

#define WIDTH	10
#define PREC	 6
#define F(v)	WIDTH, PREC, v

void print_matrix(const char *pfx, const struct matrix *m)
{
	if (pfx)
		printf("%s\n", pfx);
	printf("---------------------------\n");

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			printf("%*.*f ", F(m->cell[r][c]));
		}
		printf("\n");
	}
}


void print_coord(const char *pfx, const struct coord *c)
{
	if (pfx)
		printf("%s: ", pfx);
	printf("%*.*f, %*.*f, %*.*f, %*.*f\n",
		F(c->x), F(c->y), F(c->z), F(c->w));
}
