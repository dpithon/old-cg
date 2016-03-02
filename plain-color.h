#ifndef PLAIN_COLOR_H
#define PLAIN_COLOR_H

#include "shape.h"
#include "rgb.h"

#define PLAIN_COLOR(s)	((struct plain_color*)((s)->paint_data))

struct plain_color {
	struct rgb rgb[2];
};

extern void set_plain_colors(struct shape*, double, double, double);
extern void set_plain_color(struct shape*, int, double, double, double);

#endif /* PLAIN_COLOR_H */
