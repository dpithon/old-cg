#ifndef PARABOLOID_H
#define PARABOLOID_H

#include "shape.h"

struct paraboloid {
	SHAPE_INF;
	float a, b, c;
	float h;
};

extern struct shape *paraboloid(const struct coord*, const struct coord*,
				float, float, float, float);

#endif /* PARABOLOID_H */
