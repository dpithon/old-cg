#ifndef _BACKEND_H
#define _BACKEND_H

#include <cairo.h>

#define BLACK 	{ 0., 0., 0. }
#define WHITE 	{ 1., 1., 1. }
#define RED 	{ 1., 0., 0. }
#define GREEN 	{ 0., 1., 0. }
#define BLUE 	{ 0., 0., 1. }
#define YELLOW 	{ 1., 1., 0. }
#define MAGENTA { 1., 0., 1. }
#define CYAN 	{ 0., 1., 1. }

struct rgb {
	double r, g, b;
};

extern const struct rgb Black, White, Red, Green, Blue, Yellow, Cyan, Magenta;

cairo_surface_t *init_backend(int, int);
void release_backend(void);

int get_backend_width(void);
int get_backend_height(void);

void set_color(double, double, double);

void plot_rgb(int, int, struct rgb*);
void plot(int, int);

void shade4(const struct rgb*, const struct rgb*, 
	    const struct rgb*, const struct rgb*);

void fill(const struct rgb*);
void line(int, int, int, int);

#endif /* _BACKEND_H */
