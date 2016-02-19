#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

struct sphere {
	SHAPE_INF;
	float radius;
};

extern struct shape *sphere(const struct coord*, float);

#endif /* SPHERE_H */
