#ifndef SURFACES_H
#define SURFACES_H

#include "ipoint.h"
#include "shape.h"

struct plane {
	SHAPE_INF;
};

extern void plane(const struct coord*, const struct coord*);

#endif /* SURFACES_H */
