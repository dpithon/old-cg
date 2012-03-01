#include <gtk/gtk.h>
#include <cairo.h>
#include "backend.h"

static GtkWidget *win;

static gboolean refresh(GtkWidget *da __attribute__ ((unused)), cairo_t *cr, gpointer dat)
{
	cairo_set_source_surface(cr, (cairo_surface_t*) dat, 0, 0);
	cairo_paint(cr);

	return TRUE;
}


int gui_init(int width, int height, int argc, char *argv[])
{
	GtkWidget *da;
	cairo_surface_t *sf;

	gtk_init(&argc, &argv);

	/* create backend */
	if ((sf = be_init(width, height)) == NULL) {
		return 1;
	}

	/* create display */
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	da  = gtk_drawing_area_new();

	g_object_set(da, 
		"width-request", width,
		"height-request", height,
		NULL);
	g_object_set(win, 
		"title", "Cg display", 
		"resizable", FALSE,
		"border-width", 5,
		NULL);

	gtk_container_add(GTK_CONTAINER(win), da);
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(da, "draw", G_CALLBACK(refresh), sf);

	gtk_widget_show_all(win);

	return 0;
}


void gui_main(void)
{
	gtk_main();
	be_release();
}
