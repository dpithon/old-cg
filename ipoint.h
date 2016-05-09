#ifndef IPOINT_H
#define IPOINT_H

#include "types.h"
#include "vmath.h"

#define INSIDE	1
#define OUTSIDE	2
#define OVER	4
#define UNDER	8

#define is_inside(i)	((i)->flags & INSIDE)
#define is_outside(i)	((i)->flags & OUTSIDE)
#define is_over(i)	((i)->flags & OVER)
#define is_under(i)	((i)->flags & UNDER)
#define is_defined(i)	((i)->flags)

#define x(i)		(((struct coord*)i)->x)
#define y(i)		(((struct coord*)i)->y)
#define w(i)		(((struct coord*)i)->w)
#define z(i)		(((struct coord*)i)->z)

struct ipoint {
	struct coord i;
	const struct shape *shape;
	int    flags;
	double  k;
};

extern void reset_ipoint(struct ipoint*);
extern void set_ipoint(struct ipoint*, const struct shape*, const struct ray*,
		       int, double);

#endif /* IPOINT_H */
