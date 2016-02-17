#ifndef _SCENE_H
#define _SCENE_H

#include "math/math.h"
#include "ipoint.h"

extern void set_location(float, float, float);
extern void set_target(float, float, float);
extern bool intersect(ipoint_t*, const coord_t*);

extern coord_t Location;
extern coord_t Target;

#endif /* _SCENE_H */
