#ifndef SURFACES_H
#define SURFACES_H

#include "shape.h"

extern struct shape *plane(const struct coord*, const struct coord*);
extern struct shape *sphere(const struct coord*, float);
extern struct shape *paraboloid(const struct coord*, const struct coord*,
				float, float, float, float);
extern struct shape *cylinder(const struct coord*, const struct coord*,
			      float, float);
extern struct shape *cone(const struct coord*, const struct coord*,
			  float, float);

#endif /* SURFACES_H */
