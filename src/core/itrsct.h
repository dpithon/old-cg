#ifndef ITRSCT_H
#define ITRSCT_H

#include "dlist.h"


struct itrsct {
	struct dlink dlink;
	double k1;
	double k2;
	int exists;
};

extern void *alloc_in_itrsct_pool(size_t);

#endif /* ITRSCT_H */
