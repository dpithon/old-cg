#ifndef CONE_H
#define CONE_H

#include "shape.h"

struct cone {
	SHAPE_INF;
	float r;
	float h;
};

extern struct shape *cone(const struct coord*, const struct coord*,
			  float, float);

#endif /* CONE_H */
