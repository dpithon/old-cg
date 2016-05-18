#ifndef PIXMAP_H
#define PIXMAP_H

#include "types.h"

extern int  init_pixmap(int, int);
extern int  set_pixel(int, int, struct rgb*);
extern int  write_pixmap(const char*);
extern void release_pixmap(void);

extern int  pixmap_size(void);
extern int  pixmap_width(void);
extern int  pixmap_height(void);

#endif /* PIXMAP_H */
