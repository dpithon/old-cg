/**
 * Basic pixmap package.
 *
 */

#ifndef PIXMAP_H
#define PIXMAP_H

#include "types.h"

#define FORMAT_PPM 1

int init_pixmap(int, int);
int set_pixel(int, int, struct rgb*);
int write_pixmap(int, const char*);

#endif /* PIXMAP_H */
