#include "display_controller.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 20

static void display_run(void)
{
	tinygl_update();
}

task* init_display_controller(void)
{
	tinygl_init(1000);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	static task display_task;
	
	display_task.run = display_run;
	display_task.period = 1;
	
	return &display_task;
}
