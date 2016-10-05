#pragma once

#include <stdbool.h>

typedef enum {
	RESULT_NONE,
	RESULT_PAPER,
	RESULT_SCISSORS,
	RESULT_ROCK,
	RESULT_CONFIRMED,
} Result;

#define PAPER '='
#define SCISSORS '>'
#define ROCK '<'

void communication_initialise(void);
void send_type(char type);
void send_confirmation(void);
Result get_result(void);
