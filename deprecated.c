#include <stdlib.h>
#include <time.h>

#define FACTOR  1000.

static int first = 1;

static void random_coord(struct coord *c)
{
	int sx, sy, sz;

	if (first) {
		srand(time(NULL));
		first = 0;
	}

	sx = ((double)rand()/(double)(RAND_MAX)) > .5? 1. : -1.;
	sy = ((double)rand()/(double)(RAND_MAX)) > .5? 1. : -1.;
	sz = ((double)rand()/(double)(RAND_MAX)) > .5? 1. : -1.;

	c->x = sx * ((double)rand()/(double)(RAND_MAX)) * FACTOR;
	c->y = sy * ((double)rand()/(double)(RAND_MAX)) * FACTOR;
	c->z = sz * ((double)rand()/(double)(RAND_MAX)) * FACTOR;
}


void random_point(struct coord *p)
{
	random_coord(p);
	p->w = 1.;
}


void random_vector(struct coord *p)
{
	random_coord(p);
	p->w = 0.;
}


