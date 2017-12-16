#include <assert.h>

#include "log.h"
#include "pool.h"
#include "quadric.h"
#include "stack.h"
#include "shape.i"


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
		struct coord vec;
		vector(&vec, base, apex);
		q->h    = set_cs(SHAPE(q), base, &vec);
		q->h2   = q->h * q->h;
		q->hr2  = q->h  / q->r2;
		q->h2r2 = q->h2 / q->r2;
	} else {
		SHAPE(q)->cs.o = *base;
		SHAPE(q)->cs.i = vector_i;
		SHAPE(q)->cs.j = vector_j;
		SHAPE(q)->cs.k = vector_k;
		transform(&SHAPE(q)->cs.o);
		transform(&SHAPE(q)->cs.i);
		transform(&SHAPE(q)->cs.j);
		transform(&SHAPE(q)->cs.k);
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
