#include "nav_switch.h"
#include "navswitch.h"

static void display_run(void)
{
	navswitch_update();
}

task* init_navswitch(void)
{
	navswitch_init();
	static task display_task;
	
	display_task.run = display_run;
	display_task.period = 1;
	
	
	
	return &display_task;
}
