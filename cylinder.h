#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape.h"

struct cylinder {
	SHAPE_INF;
	float radius;
	float h;
};

extern struct shape *cylinder(const struct coord*, const struct coord*,
			      float, float);

#endif /* CYLINDER_H */
