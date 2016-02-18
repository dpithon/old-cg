#ifndef IPOINT_H
#define IPOINT_H

#include <float.h>

#include "types.h"
#include "vmath.h"

#define FLAG_DEFINED	 1
#define FLAG_INSIDE	 2
#define FLAG_OUTSIDE	 4
#define FLAG_OVER	 8
#define FLAG_UNDER	16

#define is_inside(i)	((i)->flags & FLAG_INSIDE)
#define is_outside(i)	((i)->flags & FLAG_OUTSIDE)
#define is_over(i)	((i)->flags & FLAG_OVER)
#define is_under(i)	((i)->flags & FLAG_UNDER)
#define is_defined(i)	((i)->flags & FLAG_DEFINED)

#define reset_ipoint(i)	(i)->flags = 0;\
			(i)->k = FLT_MAX

struct ipoint {
	struct coord i;
	float  k;
	int    flags;
	struct shape *shape;
};

#endif /* IPOINT_H */
