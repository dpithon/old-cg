#ifndef MATERIAL_H
#define MATERIAL_H

#include "types.h"
#include "ipoint.h"
#include "shape.h"

#define CAST_MATERIAL(m)	((struct material*)m)
#define MATERIAL_BASIC		intrinsic_f get_intrinsic

struct material {
	MATERIAL_BASIC;
};

extern void plain_color(struct shape*, int, double, double, double);
extern void plain_colors(struct shape *shp,
				      double, double, double,
				      double, double, double);
extern void pattern_stripes(struct shape *shp, int, double,
				 double, double, double,
				 double, double, double);
extern void pattern_checker(struct shape *shp, int, double,
				 double, double, double,
				 double, double, double);
extern void pattern_circle(struct shape *shp, int, double,
					double, double, double,
					double, double, double);

static inline void get_intrinsic(struct rgb *rgb, const struct ipoint *i)
{
	int n = 0;

	if (is_inside(i) || is_under(i))
		n = 1;

	i->shape->material[n]->get_intrinsic(
		rgb, i, i->shape->material[n]
	);
}

#endif /* MATERIAL_H */
