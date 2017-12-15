#include <assert.h>

#include "log.h"
#include "pool.h"
#include "quadric.h"
#include "stack.h"


/**
 * set_cs: compute local coordinate system
 *
 * q: shape
 * base, apex: extremum points
 *
 * return length between base and apex
 */
static double set_cs(struct shape *q, const struct coord *base,
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


struct shape *quadric(int shape_type, const struct coord *base,
		      const struct coord *apex,
		      double r, intersect_f intersect, normal_f normal)
{
	assert_is_point(base);
	assert(r > 0.);

	struct quadric *q = alloc_shape(quadric);
	q->r    = r;
	q->r2   = r * r;

	if (apex) {
		assert_is_point(apex);
		q->h    = set_cs(SHAPE(q), base, apex);
		q->h2   = q->h * q->h;
		q->hr2  = q->h  / q->r2;
		q->h2r2 = q->h2 / q->r2;
	} else {
		SHAPE(q)->cs.o = *base;
		SHAPE(q)->cs.i = vector_i;
		SHAPE(q)->cs.j = vector_j;
		SHAPE(q)->cs.k = vector_k;
	}

	assert_is_cartesian_coord_system(
		&SHAPE(q)->cs.i,
		&SHAPE(q)->cs.j,
		&SHAPE(q)->cs.k
	);
	change_of_coord_mat(&SHAPE(q)->cs);

	SHAPE(q)->shape_type = shape_type;
	register_intersect_function(shape_type, intersect);
	register_normal_function(shape_type, normal);

	return SHAPE(q);
}
