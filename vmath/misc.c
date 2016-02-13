#include <stdlib.h>
#include "core.h"

#define FACTOR  1000.F

static int first = 1;

static void random_coord(coord_t *c)
{
	int sx, sy, sz;

	if (first) {
		sranddev();
		first = 0;
	}

	sx = ((float)rand()/(float)(RAND_MAX)) > .5F? 1.F : -1.F;
	sy = ((float)rand()/(float)(RAND_MAX)) > .5F? 1.F : -1.F;
	sz = ((float)rand()/(float)(RAND_MAX)) > .5F? 1.F : -1.F;

	c->x = sx * ((float)rand()/(float)(RAND_MAX)) * FACTOR;
	c->y = sy * ((float)rand()/(float)(RAND_MAX)) * FACTOR;
	c->z = sz * ((float)rand()/(float)(RAND_MAX)) * FACTOR;
}


void random_point(coord_t *p)
{
	random_coord(p);
	p->w = 1.F;
}


void random_vector(coord_t *p)
{
	random_coord(p);
	p->w = 0.F;
}


