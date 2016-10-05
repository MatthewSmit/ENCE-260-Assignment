#include "display_controller.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 10

static void display_run(void)
{
	tinygl_update();
}

task* init_display_controller(void)
{
	tinygl_init(1000);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
	
	static task display_task;
	
	display_task.run = display_run;
	display_task.period = 1;
	
	return &display_task;
}
