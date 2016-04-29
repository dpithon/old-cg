#include <assert.h>

#include "quadric.h"
#include "stack.h"
#include "log.h"
#include "mm.h"
#include "painter.h"

/**
 * set_cs: compute local coordinate system
 *
 * q: quadric
 * base, apex: extremum points
 *
 * return length between base and apex
 */
static double set_cs(struct quadric *q, const struct coord *base,
		   const struct coord *apex)
{
	double f;
	struct coord vec;

	vector(&vec, base, apex);
	normalize(&q->cs.j, &vec);
	q->cs.o = *base;

	transform(&q->cs.j);
	transform(&q->cs.o);

	if (is_collinear(&q->cs.j, &vector_j, &f)) {
		if (f > 0.) {
			q->cs.i = vector_i;
			q->cs.k = vector_k;
		} else {
			q->cs.i = vector_k;
			q->cs.k = vector_i;
		}
	} else {
		cross(&q->cs.k, &q->cs.j, &vector_j);
		normalize_in_place(&q->cs.k);
		cross(&q->cs.i, &q->cs.j, &q->cs.k);
	}

	return len(&vec);
}


struct shape *quadric(const struct coord *base, const struct coord *apex,
		      double r, intersector intersect)
{
	assert_is_point(base);
	assert(r > 0.);

	struct quadric *q = alloc_struct(quadric);
	q->r    = r;
	q->r2   = r * r;

	if (apex) {
		assert_is_point(apex);
		q->h    = set_cs(q, base, apex);
		q->h2   = q->h * q->h;
		q->hr2  = q->h  / q->r2;
		q->h2r2 = q->h2 / q->r2;
	} else {
		q->cs.o = *base;
		q->cs.i = vector_i;
		q->cs.j = vector_j;
		q->cs.k = vector_k;
	}

	assert_is_cartesian_coord_system(&q->cs.i, &q->cs.j, &q->cs.k);
	change_of_coord_mat(&q->cs);

	q->intersect  = intersect;
	q->paint      = default_painter;
	q->paint_data = 0;

	return CAST_SHAPE(q);
}

