#pragma once

#include <stdint.h>

typedef void (*task_function)(void);

struct task_t
{
	// Function pointer to task
	task_function run;
	// How often task should run, in MS
	uint16_t period;
	// Current tick, used internally
	uint16_t tick;
};

typedef struct task_t task;

void scheduler_init(task** tasks);
