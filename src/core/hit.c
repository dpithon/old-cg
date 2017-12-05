#include <float.h>

#include "hit.h"
#include "ray.h"

void reset_hit(struct hit *i)
{
	i->side = NONE;
	i->k = DBL_MAX;
}


void set_hit(struct hit *i, const struct shape *shp,
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
