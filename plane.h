#ifndef PLANE_H
#define PLANE_H

#include "shape.h"

struct plane {
	SHAPE_INF;
};

extern struct shape *plane(const struct coord*, const struct coord*);

#endif /* PLANE_H */
