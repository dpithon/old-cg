#include "pool.h"
#include "shape.h"


#define SHAPE_POOL_SZ	1 * MEGA


void *alloc_in_shape_pool(size_t sz)
{
	static int pool_id = -1;

	if (pool_id < 0)
		pool_id = pool_init(SHAPE_POOL_SZ);

	return pool_alloc(pool_id, sz);
}
