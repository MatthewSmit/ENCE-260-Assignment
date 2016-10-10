/**
 @file display_controller.c
 @author Matthew Smit, mjs351  & Joseph Hill, jhi56
 @date 10/10/16
 @brief controls config for the display
 */

#include "display_controller.h"
#include "tinygl.h"
#include "font5x7_3.h"

#define MESSAGE_RATE 20

static void display_run(void)
{
	tinygl_update();
}

task* init_display_controller(void)
{
	tinygl_init(100);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
	static task display_task;
	
	display_task.run = display_run;
	display_task.period = 10;
	
	return &display_task;
}
