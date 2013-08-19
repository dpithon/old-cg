#include <stdio.h>
#include "core.h"
#include "mstack.h"
#include "io.h"

void printc(const char *fmt, coord_st *c)
{
	static char val[30];

	sprintf(val, "%5.2f %5.2f %5.2f %5.2f", c->x, c->y, c->z, c->w);
	if (fmt) {
		printf(fmt, val);
	} else {
		printf("%s", val);
	}
}


void printm(const char *fmt, matrix_st *m)
{
	int i;
	for (i = 0; i < 4; i++) {
		printc(fmt, (coord_st*) m->cell[i]);
		if (! fmt) {
			printf("\n");
		}
	}
}


void prints(const char *fmt, mstack_st *s)
{
	int i = s->i;
	while (i >= 0) {
		printm(fmt, &(s->m[i--]));
		printf("\n");
	}

	printf("-------------------------------------\n");
}


#ifdef COUNTERS
void print_counters(counter_st *cnt)
{
	unsigned long *ul = (unsigned long*) cnt;

	for (int i = 0; counter_name[i]; i++) {
		printf("%6ld ..... %s\n", ul[i], counter_name[i]);
	}
}
#endif /* COUNTERS */
