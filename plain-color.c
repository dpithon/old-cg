#include <stdlib.h>
#include "plain-color.h"

void set_plain_color(struct shape *s, struct rgb **rgbs)
{
	s->paint_data = malloc(sizeof(struct plain_color));

	PLAIN_COLOR(s)->inside  = *rgbs[0];
	PLAIN_COLOR(s)->outside = *rgbs[1];
	PLAIN_COLOR(s)->over    = *rgbs[2];
	PLAIN_COLOR(s)->under   = *rgbs[3];
}
