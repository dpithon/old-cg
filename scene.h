#ifndef _SCENE_H
#define _SCENE_H

#include "math/math.h"
#include "ray.h"
#include "ipoint.h"
#include "color.h"
#include "shape.h"

extern void set_location(float, float, float);
extern void set_target(float, float, float);
extern bool intersect(ipoint_t*, const ray_t*);
extern void add_shape(shape_t*);
extern void prepare_shape_matrices(const ccs_t*);

extern coord_t Location;
extern coord_t Target;

#endif /* _SCENE_H */
