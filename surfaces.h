#ifndef SURFACES_H
#define SURFACES_H

#include "shape.h"

extern struct shape *plane(const struct coord*, const struct coord*);
extern struct shape *sphere(const struct coord*, double);
extern struct shape *paraboloid(const struct coord*, const struct coord*,
				double, double, double, double);
extern struct shape *cylinder(const struct coord*, const struct coord*,
			      double, double);
struct shape *cone(const struct coord*, const struct coord*, double);

#endif /* SURFACES_H */
