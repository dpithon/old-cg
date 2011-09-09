#ifndef _BACKEND_H
#define _BACKEND_H

#include <cairo.h>

cairo_surface_t *init_backend(int, int);
void release_backend(void);

void plot_rgb(int, int, unsigned char, unsigned char, unsigned char);
void set_rgb(unsigned char, unsigned char, unsigned char);
void plot(int, int);
int get_backend_width(void);
int get_backend_height(void);

#endif /* _BACKEND_H */
