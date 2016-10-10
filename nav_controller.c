/**
 @file nav_controller.c
 @author Matthew Smit, mjs351  & Joseph Hill, jhi56
 @date 10/10/16
 @brief handles updating the navswitch
 */
 
#include "nav_controller.h"
#include "navswitch.h"

//updates the navswitch
static void navswitch_run(void)
{
	navswitch_update();
}

//initialise the navswitch controller
task* init_navswitch_controller(void)
{
	navswitch_init();
	
	static task navswitch_task;
	
	navswitch_task.run = navswitch_run;
	navswitch_task.period = 1;
	
	return &navswitch_task;
}
