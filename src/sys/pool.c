#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "log.h"
#include "pool.priv.h"
#include "pool.h"
#include "macros.h"


void pool_init(struct pool *pool, size_t sz)
{
	char *mem;

	if (sz % ALIGNMENT) {
		warning("pool_init: force size alignment");
		sz = align(sz, ALIGNMENT);
	}

	mem = malloc(sz);
	assert(is_ptr_aligned(mem, ALIGNMENT));

	if (mem == NULL)
		fatal("pool_init: failed to alloc memory");

	pool->top = mem + sz;
	pool->bottom = pool->free = mem;
}


void *pool_alloc(struct pool *pool, size_t sz)
{
	char *mem = pool->free;
	assert(is_ptr_aligned(mem, ALIGNMENT));

	if (mem + sz > pool->top)
		fatal("pool overflow");

	if (sz % ALIGNMENT) {
		warning("pool_alloc: force alignment");
		sz = align(sz, ALIGNMENT);
	}
	pool->free += sz;

	return mem;
}


void pool_reset(struct pool *pool)
{
	pool->free = pool->bottom;
}


void pool_free(struct pool *pool)
{
	free(pool->bottom);
	pool->free = pool->bottom = pool->top = NULL;
}
