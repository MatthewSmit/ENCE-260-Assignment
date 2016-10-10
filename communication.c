/**
 @file communication.c
 @author Matthew Smit, mjs351  & Joseph Hill, jhi56
 @date 10/10/16
 @brief controls the processes that happen between the two MCPs
 */

#include "communication.h"
#include "ir_serial.h"
#include <stdbool.h>

// Used to acknowledge that they have recieved our character
#define ACK 'X'

static char our_character;
static char opponent_character;
static bool recieved_ack;

static void comm_run(void)
{
	// Only send every 100ms to prevent lag
	static int timer = 0;
	if (timer++ >= 100)
	{
		if (our_character != 0)
			ir_serial_transmit(our_character);
		timer = 0;
	}
	
	// Process data if it exists
	uint8_t data;
	ir_serial_ret_t result = ir_serial_receive(&data);
	if (result == IR_SERIAL_OK)
	{
		switch (data)
		{
			case ROCK:
			case SCISSORS:
			case PAPER:
				opponent_character = data;
				ir_serial_transmit(ACK);
				break;
			case ACK:
				recieved_ack = true;
				break;
		}
	}
}

task* communication_initialise(void)
{
	ir_serial_init();
	
	static task comm_task;
	
	comm_task.run = comm_run;
	comm_task.period = 1;
	
	return &comm_task;
}

// Resets communication to reset internal state
void communication_reset(void)
{
	our_character = 0;
	opponent_character = 0;
	recieved_ack = false;
}

// Sets the character type for the communcation manager to send to opponent
void communication_set_type(char type)
{
	our_character = type;
}

// Returns the opponent character or null
char communication_get_opponent(void)
{
	if (opponent_character != 0 && recieved_ack)
		return opponent_character;
	return 0;
}
