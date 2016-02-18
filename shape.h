#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include "vmath.h"

#define CAST_SHAPE(s) ((struct shape*)(s))

#define SHAPE_INF struct shape *next;\
		  struct coord_system cs;\
		  struct matrix cam_to_shp;\
		  struct matrix shp_to_cam;\
		  bool (*intersect)(struct ipoint*, const struct ray*, const struct shape*);\
		  void (*intrinsic_color)(struct rgb*, struct ipoint*)

struct shape {
	SHAPE_INF;
};
	
#endif /* SHAPE_H */
