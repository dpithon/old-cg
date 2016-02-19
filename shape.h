#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include "vmath.h"

#define CAST_SHAPE(s) ((struct shape*)(s))

#define SHAPE_INF struct shape *next;\
		  struct coord_system cs;\
		  struct matrix cam_to_shp;\
		  struct matrix shp_to_cam;\
		  void  *paint_data;\
		  intersector intersect;\
		  painter paint

struct shape {
	SHAPE_INF;
};
	
#endif /* SHAPE_H */
