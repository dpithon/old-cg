#ifndef MEMCELLS_H
#define MEMCELLS_H

/*
 * memcells means memory cell
 * it manages a pool of equal size cells
 *
 * you can configure size of cell and count of memory cells you want
 *
 * +-- memcells base address
 * |
 * V
 * 
 * |-- stack --|...|------------- cells --------------|
 * |           |   |..................................|
 * |-----------|...|----------------------------------|
 *
 *                 ^
 *                 |
 *                 +--- cells base address (ALIGNMENT bytes aligned)
 *
 */

struct memcells {
	void *stack;
	void *cells;
	size_t cell_sz;
	int pool_id;
	int count;
	int top;

};

#define NEW_POOL	-1

#define memcells_config(mc, p, c, s) \
	mc.pool_id = p;\
	mc.count   = c;\
	mc.cell_sz = s;\

extern void  memcells_init(struct memcells*);
extern char *memcells_alloc(struct memcells*);
extern void  memcells_free(struct memcells*, char*);
extern int   memcells_remaining(struct memcells*);


#endif /* MEMCELLS_H */
