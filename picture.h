#ifndef PICTURE_H
#define PICTURE_H

#include "vmath.h"
#include "rgb.h"

extern bool init_picture(int, int);
extern void set_default_color(const struct rgb*);
extern void set_pixel(int, int, const struct rgb*);
extern bool save_picture(const char*);

#endif /* PICTURE_H */
