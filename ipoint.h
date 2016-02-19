#ifndef IPOINT_H
#define IPOINT_H

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

#define x(i)		(((struct coord*)i)->x)
#define y(i)		(((struct coord*)i)->y)
#define w(i)		(((struct coord*)i)->w)
#define z(i)		(((struct coord*)i)->z)

struct ipoint {
	struct coord i;
	const struct shape *shape;
	int    flags;
	float  k;
};

extern void reset_ipoint(struct ipoint*);
extern void set_ipoint(struct ipoint*, const struct shape*, int, float);

#endif /* IPOINT_H */
