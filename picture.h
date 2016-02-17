#ifndef _PICTURE_H
#define _PICTURE_H

#include "math/math.h"
#include "color.h"

extern bool init_picture(int, int, const rgb_t*);
extern void set_pixel(int, int, const rgb_t*);
extern bool save_picture(const char*);


#endif /* _PICTURE_H */
