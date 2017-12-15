#include "hit.h"
#include "pool.h"
#include "shape.h"
#include "shape.i"


#define SHAPE_POOL_SZ	1 * MEGA

intersect_f intersect_func[SHAPE_MAX_ID];
normal_f    normal_func[SHAPE_MAX_ID];


void *alloc_in_shape_pool(size_t sz)
{
	static int pool_id = -1;

	if (pool_id < 0)
		pool_id = pool_init(SHAPE_POOL_SZ);

	return pool_alloc(pool_id, sz);
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


