#include <gtk/gtk.h>
#include <cairo.h>
#include "backend.h"

#define WIDTH	512
#define HEIGHT	512

static GtkWidget *win;

gboolean refresh(GtkWidget *da __attribute__ ((unused)), cairo_t *cr, gpointer dat)
{
	cairo_set_source_surface(cr, (cairo_surface_t*) dat, 0, 0);
	cairo_paint(cr);

	return TRUE;
}


int gui_init(int argc, char *argv[])
{
	GtkWidget *da;
	cairo_surface_t *sf;

	gtk_init(&argc, &argv);

	/* create backend */
	if ((sf = be_init(WIDTH, HEIGHT)) == NULL) {
		return 1;
	}

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

	return 0;
}


void gui_show(void)
{
	gtk_widget_show_all(win);
	gtk_main();
	be_release();
}
