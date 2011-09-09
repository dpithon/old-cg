#ifndef _BACKEND_H
#define _BACKEND_H

#include <cairo.h>

#define BLACK 	{ 0, 0, 0 }
#define WHITE 	{ 255, 255, 255 }
#define RED 	{ 255, 0, 0 }
#define GREEN 	{ 0, 255, 0 }
#define BLUE 	{ 0, 0, 255 }
#define YELLOW 	{ 255, 255, 0 }
#define MAGENTA { 255, 0, 255 }
#define CYAN 	{ 0, 255, 255 }

struct rgb {
	unsigned char r, g, b;
};

struct rgbd {
	double r, g, b;
};

cairo_surface_t *init_backend(int, int);
void release_backend(void);

void plot_rgb(int, int, struct rgb*);
void plot_rgbd(int x, int y, struct rgbd *col);
void set_rgb(unsigned char, unsigned char, unsigned char);
void plot(int, int);
int get_backend_width(void);
int get_backend_height(void);

#endif /* _BACKEND_H */
