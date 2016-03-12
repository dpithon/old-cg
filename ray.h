#ifndef RAY_H
#define RAY_H

#include "vmath.h"

#define Vx	(ray->v.x)
#define Vy	(ray->v.y)
#define Vz	(ray->v.z)
#define Sx	(ray->s.x)
#define Sy	(ray->s.y)
#define Sz	(ray->s.z)

struct ray {
	struct coord s;
	struct coord v;
};

#endif /* RAY_H */
