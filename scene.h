#ifndef _SCENE_H
#define _SCENE_H

#include "math/math.h"
#include "ray.h"
#include "ipoint.h"
#include "color.h"

#define SHAPE_INF struct shape *next;\
		  ccs_t cam_to_loc;\
		  ccs_t loc_to_cam;\
		  bool (*intersect)(ipoint_t*, const ray_t*);\
		  void (*intrinsic_color)(rgb_t*, ipoint_t*)

typedef struct shape {
	SHAPE_INF;
} shape_t;

extern void set_location(float, float, float);
extern void set_target(float, float, float);
extern bool intersect(ipoint_t*, const ray_t*);
extern void add_shape(shape_t*);

extern coord_t Location;
extern coord_t Target;

#endif /* _SCENE_H */
