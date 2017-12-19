#ifndef MEMCELLS_H
#define MEMCELLS_H

#include "pool.h"

struct memcells {
	struct pool *pool;
	void **stack;
	void *heap;
	int stack_top;
	size_t cell_size;
	int cell_count;
	bool dedi_pool;
};

extern void  memcells_init(struct memcells*, struct pool*, int, size_t);
extern void  memcells_reset(struct memcells*);
extern void *memcells_lease(struct memcells*);
extern void  memcells_release(struct memcells*, void*);
extern void  memcells_free(struct memcells*);

#endif /* MEMCELLS_H */
