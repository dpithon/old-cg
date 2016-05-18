#ifndef IPOINT_H
#define IPOINT_H

#include "types.h"
#include "vmath.h"

enum side { NONE = 0, INSIDE = 1, OUTSIDE = 2, OVER = 4, UNDER = 8 };

#define x(i)		(((struct coord*)i)->x)
#define y(i)		(((struct coord*)i)->y)
#define w(i)		(((struct coord*)i)->w)
#define z(i)		(((struct coord*)i)->z)

struct ipoint {
	struct coord i;
	const struct shape *shape;
	enum side side;
	double  k;
};

static inline bool is_inside(const struct ipoint *i)
{
	return i->side == INSIDE;
}

static inline bool is_outside(const struct ipoint *i)
{
	return i->side == OUTSIDE;
}

static inline bool is_over(const struct ipoint *i)
{
	return i->side == OVER;
}

static inline bool is_under(const struct ipoint *i)
{
	return i->side == UNDER;
}

static inline bool is_defined(const struct ipoint *i)
{
	return i->side;
}


extern void reset_ipoint(struct ipoint*);
extern void set_ipoint(struct ipoint*, const struct shape*, const struct ray*,
		       enum side, double);

#endif /* IPOINT_H */
