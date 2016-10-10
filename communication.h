#pragma once
#include "scheduler.h"

#define PAPER '='
#define SCISSORS '>'
#define ROCK '<'

// Initialises communcation and returns a scheduler task
task* communication_initialise(void);

// Resets communication to reset internal state
void communication_reset(void);
// Sets the character type for the communcation manager to send to opponent
void communication_set_type(char type);
// Returns the opponent character or null
char communication_get_opponent(void);