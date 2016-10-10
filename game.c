/**
 @file game.c
 @author Matthew Smit, mjs351  & Joseph Hill, jhi56
 @date 10/10/16
 @brief Main ame file for a PSR game
 */

#include "system.h"
#include "display_controller.h"
#include "nav_controller.h"
#include "scheduler.h"
#include "communication.h"
#include "tinygl.h"
#include "navswitch.h"
#include "led.h"
#include <stddef.h>

typedef enum {
	MENU,
	GAME_CHOOSING,
	GAME_WAITING,
	END
} State;

typedef enum {
	RESULT_TIE,
	RESULT_LOSE,
	RESULT_WIN
} GameResult;

// Current state of game
static State currentState;
// Currently selected character
static char currentSelection;

// Print a character, in step mode
static void tinygl_char(char c)
{
	tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
	char data[2];
	data[0] = c;
	data[1] = 0;
	tinygl_text(data);
}

static void show_result(GameResult result);

// Compares the two results, then changes to end state
static void result_compare(char player, char opponent)
{
	if (player == opponent)
	{
		show_result(RESULT_TIE);
	}
	else if (player == PAPER)
	{
		if (opponent == ROCK)
		{
			show_result(RESULT_WIN);
		}
		else if (opponent == SCISSORS)
		{
			show_result(RESULT_LOSE);
		}
	}
	else if (player == ROCK)
	{
		if (opponent == SCISSORS)
		{
			show_result(RESULT_WIN);
		}
		else if (opponent == PAPER)
		{
			show_result(RESULT_LOSE);
		}
	}
	else if (player == SCISSORS)
	{
		if (opponent == PAPER)
		{
			show_result(RESULT_WIN);
		}
		else if (opponent == ROCK)
		{
			show_result(RESULT_LOSE);
		}
	}
}

// Sets initial state
static void start(void)
{
	currentState = MENU;
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	tinygl_text("Welcome to < = >! Press to start");
}

// Sets state to choosing a character
static void choosing(void)
{
	currentState = GAME_CHOOSING;
	currentSelection = '<';
	
	tinygl_char(currentSelection);
}

// Sets state to waiting for opponent result
static void waiting(void)
{
	communication_set_type(currentSelection);
	currentState = GAME_WAITING;
	led_set(LED1, true);
}

// Shows the result and sets the state to end
static void show_result(GameResult result)
{
	currentState = END;
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	led_set(LED1, false);
	switch (result)
	{
		case RESULT_TIE:
			tinygl_text("Tie");
			break;
		case RESULT_LOSE:
			tinygl_text("Lose");
			break;
		case RESULT_WIN:
			tinygl_text("Win");
			break;
	}
	communication_reset();
}

//Update function for menu state
static void menu_update(void)
{
	if (navswitch_push_event_p(NAVSWITCH_PUSH))
	{
		choosing();
	}
}

//Update function for choosing state
static void choosing_update(void)
{
	if (navswitch_push_event_p(NAVSWITCH_WEST))
	{
		if (currentSelection == '<')
			currentSelection = '>';
		else currentSelection--;
		tinygl_char(currentSelection);
	}
	else if (navswitch_push_event_p(NAVSWITCH_EAST))
	{
		if (currentSelection == '>')
			currentSelection = '<';
		else currentSelection++;
		tinygl_char(currentSelection);
	}
	else if (navswitch_push_event_p(NAVSWITCH_PUSH))
	{
		waiting();
		led_set(LED1, true);
	}
}

//Update function for waiting state
static void waiting_update(void)
{
	char opponentChar = communication_get_opponent();
	if (opponentChar != 0)
	{
		result_compare(currentSelection, opponentChar);
	}
}
//Update function for end state
static void end_update(void)
{
	if (navswitch_push_event_p(NAVSWITCH_PUSH))
	{
		choosing();
	}
}

//Changes update function based on current state
static void game_update(void)
{
	switch (currentState)
	{
		case MENU:
			menu_update();
			break;
		case GAME_CHOOSING:
			choosing_update();
			break;
		case GAME_WAITING:
			waiting_update();
			break;
		case END:
			end_update();
			break;
	}
}

// Creates game task
task* init_game(void)
{
	static task game_task;
	
	game_task.run = game_update;
	game_task.period = 1;
	
	return &game_task;
}

int main(void)
{
	system_init();
	led_init();
	
	// Turn off LED light
	led_set(LED1, false);
	
	task* tasks[] =
	{
		init_navswitch_controller(),
		init_display_controller(),
		communication_initialise(),
		init_game(),
		NULL
	};
	
    start();
	scheduler_init(tasks);
}
