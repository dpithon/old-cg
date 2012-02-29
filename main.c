#include "gui.h"
#include "backend.h"

int main(int argc, char *argv[])
{
	gui_init(argc, argv);

	be_set_pixel(10, 10, 0, 0, 255);
	be_set_pixel(11, 10, 0, 0, 255);
	be_set_pixel(12, 10, 0, 0, 255);
	be_set_pixel(10, 11, 0, 0, 255);
	be_set_pixel(11, 11, 0, 0, 255);
	be_set_pixel(12, 11, 0, 0, 255);

	gui_show();

	return 0;
}
