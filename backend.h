#ifndef _BACKEND_H
#define _BACKEND_H

#include <cairo.h>

cairo_surface_t *be_init(int, int);
void be_release(void);

int be_get_width(void);
int be_get_height(void);

void be_set_pixel(int, int, unsigned char, unsigned char, unsigned char);
void be_get_pixel(int, int, unsigned char*, unsigned char*, unsigned char*);

#endif /* _BACKEND_H */
