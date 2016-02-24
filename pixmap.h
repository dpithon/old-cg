/**
 * Basic pixmap package.
 *
 */

#ifndef PIXMAP_H
#define PIXMAP_H

#include "types.h"

#define FORMAT_PPM 1

typedef unsigned char cval; /* color component: from 0 to 255 */


int pixmap_init(int, int);
int pixmap_cleanup(void);
int pixmap_set(int, int, cval, cval, cval);
int pixmap_get(int, int, cval*, cval*, cval*);

int pixmap_write(int, const char*);

#endif /* PIXMAP_H */
