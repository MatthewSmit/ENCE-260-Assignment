#include "scheduler.h"
#include "system.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>

#define TIMER_CLOCK_DIVISOR 64
#define TIMER_RATE (F_CPU / TIMER_CLOCK_DIVISOR)
#define TIMER_RATE_MS (TIMER_RATE / 1000)

static task** my_tasks;
static int number_tasks;

// Function called every tick to process tasks
static void scheduler_run(void)
{
	for (int i = 0; i < number_tasks; i++)
	{
		my_tasks[i]->tick++;
		if (my_tasks[i]->tick >= my_tasks[i]->period)
		{
			my_tasks[i]->run();
			my_tasks[i]->tick = 0;
		}
	}
	
	while (TCNT1 < TIMER_RATE_MS)
		;
	TCNT1 = 0;
}

// starts scheduler, tasks is in null terminated array of task pointers
void scheduler_init(task** tasks)
{
	my_tasks = tasks;
	
	for (int i = 0; ; i++)
	{
		if (tasks[i] == NULL)
		{
			number_tasks = i;
			break;
		}
		tasks[i]->tick = 0;
	}
	
	// Initialise timer setting the clock divisor to 64
	TCCR1A = 0;
	TCCR1B = 3;
	TCCR1C = 0;
	TCNT1 = 0;
	
	while (true)
		scheduler_run();
}
