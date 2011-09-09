#include <gtk/gtk.h>
#include <cairo.h>
#include "backend.h"
#include "draw.h"

#define WIDTH	256
#define HEIGHT	200


gboolean refresh(GtkWidget *da, cairo_t *cr, gpointer dat)
{
	cairo_set_source_surface(cr, (cairo_surface_t*) dat, 0, 0);
	cairo_paint(cr);

	return TRUE;
}


int main(int argc, char *argv[])
{
	GtkWidget *win, *da;
	cairo_surface_t *sf;

	gtk_init(&argc, &argv);

	/* create backend */
	if ((sf = init_backend(WIDTH, HEIGHT)) == NULL) {
		return 1;
	}

	draw();

	/* create display */
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	da  = gtk_drawing_area_new();

	g_object_set(win, 
		"title", "Cg display", 
		"width-request", WIDTH,
		"height-request", HEIGHT,
		"resizable", FALSE,
		"border-width", 5,
		NULL);

	gtk_container_add(GTK_CONTAINER(win), da);
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(da, "draw", G_CALLBACK(refresh), sf);

	gtk_widget_show_all(win);

	gtk_main();

	release_backend();

	return 0;
}
