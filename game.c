#include "system.h"
#include "display_controller.h"
#include "led_controller.h"
#include "scheduler.h"

#include <stddef.h>

int main(void)
{
	system_init();
	
	task* tasks[] =
	{
		init_display_controller(),
		init_led_controller(),
		NULL
	};
	
    tinygl_text("Hi");
	scheduler_init(tasks);
}
