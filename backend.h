#ifndef _BACKEND_H
#define _BACKEND_H

#include <cairo.h>

#define BLACK 	{   0,   0,   0 }
#define WHITE 	{ 255, 255, 255 }
#define RED 	{ 255,   0,   0 }
#define GREEN 	{   0, 255,   0 }
#define BLUE 	{   0,   0, 255 }
#define YELLOW 	{ 255, 255,   0 }
#define MAGENTA { 255,   0, 255 }
#define CYAN 	{   0, 255, 255 }

struct rgb {
	unsigned char r, g, b;
};

struct rgbd {
	double r, g, b;
};

extern const struct rgb Black, White, Red, Green, Blue, Yellow, Cyan, Magenta;

cairo_surface_t *init_backend(int, int);
void release_backend(void);

int get_backend_width(void);
int get_backend_height(void);

void set_color(unsigned char, unsigned char, unsigned char);

void plot_rgb(int, int, struct rgb*);
void plot_rgbd(int, int, struct rgbd*);
void plot(int, int);

void shade4(const struct rgb*, const struct rgb*, 
	    const struct rgb*, const struct rgb*);

#endif /* _BACKEND_H */
