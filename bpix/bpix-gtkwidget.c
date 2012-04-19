#include <gtk/gtk.h>
#include <cairo.h>
#include "bpix-core.h"
#include "bpix-error.h"
#include "bpix-cairo.h"


static gboolean refresh(GtkWidget *da __attribute__ ((unused)), 
			cairo_t *cr, gpointer dat)
{
	cairo_set_source_surface(cr, (cairo_surface_t*) dat, 0, 0);
	cairo_paint(cr);
	return TRUE;
}


static gboolean release(GtkWidget *da __attribute__ ((unused)), gpointer dat)
{
	cairo_surface_destroy((cairo_surface_t*) dat);
	return TRUE;
}


int bpix_gtkwidget_new(struct bpix *gp, GtkWidget **da)
{
	cairo_surface_t *surf;

	if (bpix_cairo_create_surface_from_bpix(gp, &surf)) {
		return 1;
	}

	if (! (*da = gtk_drawing_area_new())) {
		gp->error = BPIX_ERR_GTK;
		return 1;
	}

	g_object_set(*da, "width-request",  gp->w, 
			  "height-request", gp->h, NULL);
	g_signal_connect(*da, "destroy", G_CALLBACK(release), surf);
	g_signal_connect(*da, "draw", G_CALLBACK(refresh), surf);

	return 0;
}
