#ifndef _SURFACES_H
#define _SURFACES_H

#include "ipoint.h"
#include "shape.h"

typedef struct plane {
	SHAPE_INF;
} plane_t;

extern void plane(const coord_t*, const coord_t*);

#endif /* _SURFACES_H */
