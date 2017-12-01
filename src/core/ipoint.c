#include <float.h>

#include "ipoint.h"
#include "ray.h"

void reset_ipoint(struct ipoint *i)
{
	i->side = NONE;
	i->k = DBL_MAX;
}


void set_ipoint(struct ipoint *i, const struct shape *shp,
		const struct ray *ray, enum side s, double k)
{
	i->shape = shp;
	i->ray   = *ray;
	i->side  = s;
	i->k     = k;
	set_point((struct coord*) i,
		k * Vx + Sx,
		k * Vy + Sy,
		k * Vz + Sz
	);
}
