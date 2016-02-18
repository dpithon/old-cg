#ifndef SHAPE_H
#define SHAPE_H

#include "ray.h"
#include "ipoint.h"
#include "rgb.h"
#include "vmath.h"

#define CAST_SHAPE(s) ((struct shape*)(s))

#define SHAPE_INF struct shape *next;\
		  struct coord_system ccs;\
		  matrix_t m;\
		  matrix_t mi;\
		  bool (*intersect)(struct ipoint*, const struct ray*, const struct shape*);\
		  void (*intrinsic_color)(struct rgb*, struct ipoint*)

struct shape {
	SHAPE_INF;
};
	
#endif /* SHAPE_H */
