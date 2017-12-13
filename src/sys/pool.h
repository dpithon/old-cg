#ifndef POOL_H
#define POOL_H

#include <stdlib.h>

#define KILO  1024
#define MEGA  (KILO * 1024)


extern void  pool_set_max_pools(int max);
extern int   pool_init(size_t sz);
extern void *pool_alloc(int pool_id, size_t sz);
extern void  pool_reset(int pool_id);
extern void  pool_free(int pool_id);

#endif /* POOL_H */
