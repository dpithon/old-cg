#include "math/math.h"
#include "ray.h"
#include "ipoint.h"

coord_t Location = {100.F, 100.F, 100.F, 1.F};
coord_t Target   = POINT_O;

void set_location(float x, float y, float z)
{
	Location.x = x;
	Location.y = y;
	Location.z = z;
	Location.w = 1.F;
}

void set_target(float x, float y, float z)
{
	Target.x = x;
	Target.y = y;
	Target.z = z;
	Target.w = 1.F;
}

bool intersect(ipoint_t *i, const ray_t *r)
{
	i->flags = 0;
	if (r->v.y > .0F && r->v.x > 0.F)
		return true;
	return false;
}

