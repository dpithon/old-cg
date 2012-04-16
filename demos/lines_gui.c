#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "gpix/gpix.h"
#include "gpix/gpix-gtkwidget.h"

#define WIDTH	500
#define HEIGHT	500
#define MIN_SPARKLES 80
#define MAX_SPARKLES 300
#define NR	10

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif /* M_PI */

static GtkWidget *da;

int my_round(double v)
{
	return (int) floor(v + .5);
}


void circlines(struct gpix *gp, int xc, int yc, int n, int w, int h)
{
	int l0, l1, w1, w2, w3, w4;
	double a;

	w1 = xc;
	w2 = w - xc - 1;
	w3 = yc;
	w4 = h - yc - 1;

	w1 = w1 < w2 ? w1 : w2;
	w3 = w3 < w4 ? w3 : w4;
	w1 = w1 < w3 ? w1 : w3;

	l1 = w1;
	l0 = l1 / 4;

	for (a = 0; a < M_PI * 2.; a += M_PI * 2. / (double) n) {
		int x0 = xc + my_round(l0 * cos(a));
		int y0 = yc + my_round(l0 * sin(a));
		int x1 = xc + my_round(l1 * cos(a));
		int y1 = yc + my_round(l1 * sin(a));

		gpix_line(gp, x0, y0, x1, y1);
		g_usleep(5000UL);
		gdk_threads_enter();
		gtk_widget_queue_draw(da);
		gdk_threads_leave();
	}
}


static void draw(struct gpix *gp)
{
	int x, y, r, g, b, nr;

	for (;;) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		nr = rand() % MAX_SPARKLES + 1;
		nr = nr < MIN_SPARKLES ? MIN_SPARKLES : nr;
		gp->fg_r = r;
		gp->fg_g = g;
		gp->fg_b = b;
		circlines(gp, x, y, nr, WIDTH, HEIGHT);
		gp->fg_r = 0;
		gp->fg_g = 0;
		gp->fg_b = 0;
		circlines(gp, x, y, nr, WIDTH, HEIGHT);
	}
}


int main(int argc, char *argv[])
{
	GtkWidget *win;
	struct gpix gp = GPIX_INIT, gp_1, gp_2, gp_3, gp_4;

	g_thread_init(NULL);
	gdk_threads_init();
	
	gtk_init(&argc, &argv);

	gp.w = WIDTH;
	gp.h = HEIGHT;
	if (gpix_init(&gp)) {
		fprintf(stderr, "gpix_init error: %s\n", gpix_errstr(&gp));
		return 1;
	}
	memcpy(&gp_1, &gp, sizeof(gp));
	memcpy(&gp_2, &gp, sizeof(gp));
	memcpy(&gp_3, &gp, sizeof(gp));
	memcpy(&gp_4, &gp, sizeof(gp));

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (gpix_gtkwidget_new(&gp, &da)) {
		fprintf(stderr, "gpix_init error: %s\n", gpix_errstr(&gp));
		return 1;
	}


	g_object_set(win, 
		"title", "Cg display", 
		"resizable", FALSE,
		"border-width", 5,
		NULL);

	gtk_container_add(GTK_CONTAINER(win), da);
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(win);

	g_thread_create((GThreadFunc) draw, &gp,     FALSE, NULL);
	g_thread_create((GThreadFunc) draw, &gp_1, FALSE, NULL);
	g_thread_create((GThreadFunc) draw, &gp_2, FALSE, NULL);
	g_thread_create((GThreadFunc) draw, &gp_3, FALSE, NULL);
	g_thread_create((GThreadFunc) draw, &gp_4, FALSE, NULL);

	gtk_main();

	gpix_cleanup(&gp);
	return 0;
}