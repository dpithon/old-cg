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

extern void set_material_plain_color(struct shape*, double, double, double);
extern void set_material_plain_colors(struct shape *shp,
				      double, double, double,
				      double, double, double);

static inline void get_intrinsic(struct rgb *rgb, const struct ipoint *i)
{
	i->shape->material->get_intrinsic(
		rgb, i, i->shape->material
	);
}

#endif /* MATERIAL_H */
