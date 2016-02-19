#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "sphere.h"
#include "plane.h"
#include "rgb.h"
#include "plain-color.h"

#define W	640
#define H	480

struct rgb yellow = RGBYellow;
struct rgb blue   = RGBBlue;
struct rgb red    = RGBRed;
struct rgb green  = RGBGreen;

struct rgb white  = RGBWhite;
struct rgb magenta = RGBMagenta;
struct rgb lightgray = RGBLightGray;
struct rgb cyan = RGBCyan;

struct rgb *scol[] = {&yellow, &yellow, &yellow, &yellow };
struct rgb *pcol[] = {&red, &red, &red, &red };
struct rgb *tcol[] = {&cyan, &cyan, &cyan, &cyan };
struct rgb *ucol[] = {&green, &green, &green, &green };


int main()
{
	struct shape *s;
	struct shape *t;
	struct shape *p;
	struct shape *q;
	struct coord c = {-50.F, 0.F, -50.F, 1.F };

	set_location(90.F, 30.F, 90.F);
	set_target(-50.F, 0.F, -50.F);
	init_pinhole(W, H, 40.F);

	p = plane(&PointO, &VectorJ);
	set_plain_color(p, pcol);

	q = plane(&c, &VectorI);
	set_plain_color(q, ucol);

	s = sphere(&PointO, 180.F);
	set_plain_color(s, scol);

	t = sphere(&c, 35.F);
	set_plain_color(t, tcol);

	//add_shape(p);
	add_shape(s);
	add_shape(t);
	add_shape(q);

	prepare_shape_matrices(pinhole_coord_system());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("result.pnm");
}
