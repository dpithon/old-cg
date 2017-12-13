#include "memcells.h"
#include "pool.h"
#include "log.h"


void memcells_init(struct memcells *mc)
{
	assert(count > 0);

	char *cell;
	size_t aligned_sz, stack_sz, cells_sz;
	int n;

	if (mc->pool_id == NEW_POOL)
		mc->pool_id = pool_init(stack_sz + cells_sz);

	if (mc->cell_sz % ALIGNMENT)
		aligned_sz = ((mc->cell_sz / ALIGNMENT) + 1) * ALIGNMENT;
	else
		aligned_sz = mc->cell_sz;

	stack_sz = mc->count * sizeof(int);
	cells_sz = mc->count * aligned_sz;


	mc->stack = pool_alloc(mc->pool_id, stack_sz);
	mc->cells = pool_alloc(mc->pool_id, cells_sz);
	mc->top = mc->count;

	for (n = 0, cell = mc->cells; n < count; n++, cell += aligned_sz)
		mc->stack[n] = cell;
}


char *memcells_alloc(struct memcells *mc)
{
	if (!mc->top)
		fatal("memcells_alloc: out of cells");

	return mc->stack[--mc->top];
}


void memcells_free(struct memcells *mc, char *cell)
{
	if (mc->top > mc->count)
		fatal("memcells_free: stack overflow");
	mc->stack[mc->top++] = cell;
}


