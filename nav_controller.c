#include "nav_controller.h"
#include "navswitch.h"

static void navswitch_run(void)
{
	navswitch_update();
}

task* init_navswitch_controller(void)
{
	navswitch_init();
	
	static task navswitch_task;
	
	navswitch_task.run = navswitch_run;
	navswitch_task.period = 1;
	
	return &navswitch_task;
}
