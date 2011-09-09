#include "backend.h"
#include "shader.h"


void draw(void)
{
	struct rgb c1 = BLACK; struct rgb c2 = RED;
	struct rgb c3 = YELLOW; struct rgb c4 = CYAN;

	shade4(&c1, &c2, &c3, &c4);
}
