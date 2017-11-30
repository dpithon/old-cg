#ifndef QUADRIC_H
#define QUADRIC_H

#include "../types.h"
#include "../ray.h"

#include "shape.h"

struct quadric {
	SHAPE_BASIC;
	double r, r2;
	double h, h2;
	double hr2, h2r2;
};

#define H	((const struct quadric*)s)->h
#define H2	((const struct quadric*)s)->h2
#define R	((const struct quadric*)s)->r
#define R2	((const struct quadric*)s)->r2
#define HR2	((const struct quadric*)s)->hr2
#define H2R2	((const struct quadric*)s)->h2r2

struct shape *quadric(const struct coord*, const struct coord*,
		      double, intersect_f, normal_f);

static inline bool in_range(double k, const struct shape *s,
			    const struct ray *ray)
{
	double y = k * Vy + Sy;
	return (y >= 0. && y <= H);
}


#endif /* QUADRIC_H */
