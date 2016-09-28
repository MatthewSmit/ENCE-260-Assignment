#include "display_controller.h"
#include "display.h"

static void display_run(void)
{
	display_update();
}

task* init_display_controller(void)
{
	display_init();
	
	static task display_task;
	
	display_task.run = display_run;
	display_task.period = 1;
	
	for (int i = 0; i < DISPLAY_WIDTH; i++)
		display_pixel_set(i, 0, true);
	for (int i = 0; i < DISPLAY_WIDTH; i++)
		display_pixel_set(i, DISPLAY_HEIGHT - 1, true);
	
	return &display_task;
}
