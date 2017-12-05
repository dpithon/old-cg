#ifndef HIT_H
#define HIT_H

#include "ray.h"
#include "types.h"
#include "vmath.h"

enum side { NONE = 0, INSIDE = 1, OUTSIDE = 2, OVER = 4, UNDER = 8 };

#define x(i)		(((struct coord*)i)->x)
#define y(i)		(((struct coord*)i)->y)
#define w(i)		(((struct coord*)i)->w)
#define z(i)		(((struct coord*)i)->z)

struct hit {
	struct coord i;
	struct ray ray;
	const struct shape *shape;
	enum side side;
	double k;
};

static inline bool is_inside(const struct hit *i)
{
	return i->side == INSIDE;
}

static inline bool is_outside(const struct hit *i)
{
	return i->side == OUTSIDE;
}

static inline bool is_over(const struct hit *i)
{
	return i->side == OVER;
}

static inline bool is_under(const struct hit *i)
{
	return i->side == UNDER;
}

static inline bool is_defined(const struct hit *i)
{
	return i->side;
}


extern void reset_hit(struct hit*);
extern void set_hit(struct hit*, const struct shape*, const struct ray*,
		       enum side, double);

#endif /* HIT_H */
