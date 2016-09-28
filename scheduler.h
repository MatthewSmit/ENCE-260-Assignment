#pragma once

#include <stdint.h>

typedef void (*task_function)(void);

struct task_t
{
	task_function run;
	uint16_t period;
	uint16_t tick;
};

typedef struct task_t task;

void scheduler_init(task** tasks);
