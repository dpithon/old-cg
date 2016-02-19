#ifndef PLAIN_COLOR_H
#define PLAIN_COLOR_H

#include "shape.h"
#include "rgb.h"

#define PLAIN_COLOR(s)	((struct plain_color*)((s)->paint_data))

struct plain_color {
	struct rgb inside;
	struct rgb outside;
	struct rgb over;
	struct rgb under;
};

extern void set_plain_color(struct shape*, struct rgb**);

#endif /* PLAIN_COLOR_H */
