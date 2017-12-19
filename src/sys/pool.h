#ifndef POOL_H
#define POOL_H

#include <stdlib.h>

#define KILO  1024
#define MEGA  (KILO * 1024)

#define INIT_POOL(name)		struct pool name = {0, 0, 0}
#define INIT_STATIC_POOL(name)	static INIT_POOL(name)


struct pool {
	char *bottom;
	char *top;
	char *free;
};


extern void  pool_init(struct pool*, size_t sz);
extern void *pool_alloc(struct pool*, size_t sz);
extern void  pool_reset(struct pool*);
extern void  pool_free(struct pool*);

#endif /* POOL_H */
