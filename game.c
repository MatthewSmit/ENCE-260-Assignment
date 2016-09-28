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
	
	scheduler_init(tasks);
}










/*#include "display.h"
#include "led.h"
#include "system.h"
#include "pacer.h"






void display_update2(void);

void display_update2()
{
	for (int i = 0; i < DISPLAY_WIDTH; i++)
	{
		display_update();
		pacer_wait();
	}
}

int main(void)
{
    system_init();
    led_init();
    display_init();
    pacer_init(1000);

	led_set(LED1, true);
	
    while (1)
    {
		for (int i = 0; i < DISPLAY_WIDTH; i++)
			display_pixel_set(i, 0, true);
		for (int i = 0; i < DISPLAY_WIDTH; i++)
			display_pixel_set(i, DISPLAY_HEIGHT - 1, true);
		display_update2();
    }
}*/
