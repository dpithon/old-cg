#ifndef _IPOINT_H
#define _IPOINT_H

#include "math/math.h"

#define FLAG_DEFINED	 1
#define FLAG_INSIDE	 2
#define FLAG_OUTSIDE	 4
#define FLAG_OVER	 8
#define FLAG_UNDER	16

#define IS_INSIDE(i)	((i)->flags & FLAG_INSIDE)
#define IS_OUTSIDE(i)	((i)->flags & FLAG_OUTSIDE)
#define IS_OVER(i)	((i)->flags & FLAG_OVER)
#define IS_UNDER(i)	((i)->flags & FLAG_UNDER)
#define IS_DEFINED(i)	((i)->flags & FLAG_DEFINED)

#define RESET_IPOINT(i)	(i)->flags = 0

typedef struct ipoint {
	struct shape *shape;
	coord_t i;
	float   k;
	int     flags;
} ipoint_t;

#endif /* _IPOINT_H */
