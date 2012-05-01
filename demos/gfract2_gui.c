#include <stdio.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include <gtk/gtk.h>
#include "bpix/bpix.h"
#include "bpix/bpix-gtk.h"

#define L  	  1
#define ALPHA	 90
#define W 	1600
#define H 	1400
#define N 	 21

static char buf1[40000000] = "FX";
static char buf2[40000000];

static const char *ruleX = "X+YF";
static const char *ruleY = "FX-Y";

struct rctx {
	struct bpix *bp;
	int n;
	char *buf1;
	char *buf2;
	char *result;
	GtkWidget *widget;
};


static char *apply_rules(int n, char *s1, char *s2)
{
	int i, j;
	char *tmp, *from, *to;
	int rulex_sz=strlen(ruleX);
	int ruley_sz=strlen(ruleY);

	from = s1;
	to = s2;

	while (n-- > 0) {
		i = j = 0;
		to[0] = '\0';

		while (from[i]) {
			switch (from[i]) {
			case 'X':
				strncpy(&(to[j]), ruleX, rulex_sz);
				j += rulex_sz;
				break;
			case 'Y':
				strncpy(&(to[j]), ruleY, ruley_sz);
				j += ruley_sz;
				break;
			default:
				to[j++] = from[i];
			}

			++ i;
		}

		to[j] = 0;

		tmp = to;
		to = from;
		from = tmp;
	}

	return to;
}


static void draw(struct bpix *bp, char *to)
{
	int vcos, vsin;
	int x, y, xb, yb, alpha;
	struct gctx gc = {63, 60, 57, 105, 100, 95};

	bpix_fill(bp, &gc);

	x = bpix_get_width(bp) * 3 / 4;
	y = bpix_get_height(bp) / 3;
	alpha = vcos = vsin = 0;

	while (*to) {
		switch (*to) {
		case '-': 
			alpha -= ALPHA; 
			break;

		case '+': 
			alpha += ALPHA; 
			break;

		case 'F':
			switch (alpha % 360) {
				case -270:
				case 90:  vcos=0;  vsin=1; break;
				case -180:
				case 180: vcos=-1; vsin=0; break;
				case -90:
				case 270: vcos=0;  vsin=-1; break;
				case 0:   vcos=1;  vsin=0; break;
			}
			xb = x + L * vcos;
			yb = y + L * vsin;
			bpix_draw_linei(bp, &gc, x, y, xb, yb);
			x = xb;
			y = yb;
		}

		to++;
	}
}


static void worker(struct rctx *rc)
{
	rc->result = apply_rules(rc->n, rc->buf1, rc->buf2);
	draw(rc->bp, rc->result);
}



int main(int argc, char *argv[])
{
	GtkWidget *win, *sw, *da;
	struct bpix bp;
	struct rctx rc;

	/* init gtk */
	gtk_init(&argc, &argv);

	/* create pixmap backend */
	if (bpix_init(&bp, W, H)) {
		fprintf(stderr, "bpix_init error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}

	/* let's create the gui */
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (bpix_gtk_drawing_area_new(&bp, &da)) {
		fprintf(stderr, "bpix_init error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}


	g_object_set(win, 
		"title", "Cg display", 
		"resizable", TRUE,
		"border-width", 5,
		NULL);

	sw = gtk_scrolled_window_new(NULL, NULL);
	g_object_set(sw, "width-request", 400, "height-request", 400, NULL);

	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)sw, da);

	gtk_container_add(GTK_CONTAINER(win), sw);
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* run the worker */
	rc.bp = &bp;
	rc.n = N;
	rc.buf1 = buf1;
	rc.buf2 = buf2;
	rc.widget = da;
	worker(&rc);

	/* run the show */
	gtk_widget_show_all(win);
	gtk_main();

	bpix_pnm_write_to_file(&bp, "dragon.pnm");
	bpix_cleanup(&bp);
	return 0;
}
