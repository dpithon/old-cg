#include "hit.h"
#include "pool.h"
#include "shape.h"
#include "shape.priv.h"
#include "stack.h"


#define SHAPE_POOL_SZ	1 * MEGA

intersect_f intersect_func[SHAPE_MAX_ID];
normal_f    normal_func[SHAPE_MAX_ID];


void *alloc_in_shape_pool(size_t sz)
{
	INIT_STATIC_POOL(pool);

	if (pool.bottom == 0)
		pool_init(&pool, SHAPE_POOL_SZ);

	return pool_alloc(&pool, sz);
}


void register_intersect_function(int shape_type, intersect_f f)
{
	intersect_func[shape_type] = f;
}


void register_normal_function(int shape_type, normal_f f)
{
	normal_func[shape_type] = f;
}


bool intersect(struct hit *hit, const struct ray *ray, const struct shape *shape)
{
	return intersect_func[shape->shape_type](hit, ray, shape);
}


void normal(struct coord *norm, const struct hit *h)
{
	normal_func[h->shape->shape_type](norm, COORD(h));
}


/**
 * set_cs: compute local coordinate system
 *
 * q: shape
 * v: vector 
 *
 * return length between base and apex
 */
double set_cs(struct shape *q, const struct coord *base, const struct coord *v)
{
	double f;

	normalize(&q->cs.j, v);
	q->cs.o = *base;

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

	transform(&q->cs.i);
	transform(&q->cs.j);
	transform(&q->cs.k);
	transform(&q->cs.o);

	return len(v);
}
