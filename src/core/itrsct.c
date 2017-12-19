#include "pool.h"

#define ITRSCT_	(64 * KILO)

void *alloc_in_itrsct_pool(size_t sz)
{
	static int mc_id = -1;

	if (mc_id < 0)
		mc_id = memcells_init(ITRSCT_COUNT, sizeof(struct itrsct));

	return memcells_alloc(mc_id);
}

