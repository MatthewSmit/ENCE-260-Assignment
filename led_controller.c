#include "led_controller.h"
#include "led.h"

static bool state = true;

static void led_run(void)
{
	led_set(LED1, state);
	state = !state;
}

task* init_led_controller(void)
{
	led_init();
	
	static task led_task;
	
	led_task.run = led_run;
	led_task.period = 500;
	
	return &led_task;
}
