#ifndef _IPOINT_H
#define _IPOINT_H

#include "math/math.h"

#define FLAG_INSIDE	1
#define FLAG_OUTSIDE	2
#define FLAG_OVER	4
#define FLAG_UNDER	8

#define IS_INSIDE(i)	((i)->flags & FLAG_INSIDE)
#define IS_OUTSIDE(i)	((i)->flags & FLAG_OUTSIDE)
#define IS_OVER(i)	((i)->flags & FLAG_OVER)
#define IS_UNDER(i)	((i)->flags & FLAG_UNDER)

typedef struct ipoint {
	struct shape *shape;
	coord_t i;
	float   dist;
	int     flags;
} ipoint_t;

#endif /* _IPOINT_H */
