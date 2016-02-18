#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

struct sphere {
	SHAPE_INF;
	float radius;
};

extern struct sphere *sphere(const struct coord*, float);

#endif /* SPHERE_H */
