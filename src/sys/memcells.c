#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "log.h"
#include "pool.h"
#include "pool.priv.h"
#include "memcells.h"


void memcells_init(struct memcells *mc, struct pool *pool,
			int count, size_t sz)
{
	size_t stack_size, heap_size;

	assert(count > 0);

	mc->cell_count = count;
	if (sz % ALIGNMENT) {
		warning("memcells_init: force size alignment");
		mc->cell_size = align(sz, ALIGNMENT);
	} else {
		mc->cell_size = sz;
	}

	stack_size = count * sizeof(int);
	heap_size = count * mc->cell_size;

	mc->pool = pool;
	if (mc->pool->bottom == 0) {
		size_t total_size = stack_size + heap_size;
		if (total_size % ALIGNMENT)
			total_size = align(total_size, ALIGNMENT);

		pool_init(mc->pool, total_size);
		mc->dedi_pool = true;
	} else {
		mc->dedi_pool = false;
	}

	mc->stack = pool_alloc(mc->pool, stack_size);
	mc->heap = pool_alloc(mc->pool, heap_size);

	memcells_reset(mc);
}


void memcells_reset(struct memcells *mc)
{
	char *cell = mc->heap;
	for (int n = 0; n < mc->cell_count; n++) {
		// TODO loop from mc->stack_top  mc->cell_count
		mc->stack[n] = cell;
		cell += mc->cell_size;
	}
	mc->stack_top = mc->cell_count;
}


void *memcells_lease(struct memcells *mc)
{
	if(!mc->stack_top)
		fatal("memcells_lease: no more cells");
	return mc->stack[--mc->stack_top];
}


void memcells_release(struct memcells *mc, void *ptr)
{
	if (mc->stack_top == mc->cell_count)
		fatal("memcells_release: stack overflow");
	mc->stack[mc->stack_top++] = ptr;
}


void memcells_free(struct memcells *mc)
{
	if (mc->dedi_pool) {
		pool_free(mc->pool);
	}
}
