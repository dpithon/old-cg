#ifndef _SHAPE_H
#define _SHAPE_H

#include "ray.h"
#include "ipoint.h"
#include "color.h"
#include "math/math.h"

#define CAST_SHAPE(s) ((shape_t*)(s))

#define SHAPE_INF struct shape *next;\
		  ccs_t ccs;\
		  matrix_t m;\
		  matrix_t mi;\
		  bool (*intersect)(ipoint_t*, const ray_t*, const struct shape*);\
		  void (*intrinsic_color)(rgb_t*, ipoint_t*)

typedef struct shape {
	SHAPE_INF;
} shape_t;
	
#endif /* _SHAPE_H */
