#include "system.h"
#include "display_controller.h"
#include "led_controller.h"
#include "nav_controller.h"
#include "scheduler.h"
#include "communication.h"
#include "tinygl.h"
#include "navswitch.h"
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

State currentState = MENU;

void start(void) {
	currentState = MENU;
	tinygl_text("< = >");
}

void choosing(void){
	/* use a number to determine choice*/
}

void show_result(GameResult result) {
	switch (result)
	{
		case RESULT_TIE:
			tinygl_text("Tie");
			break;
		case RESULT_LOSE:
			tinygl_text("You Lose");
			break;
		case RESULT_WIN:
			tinygl_text("You Win");
			break;
	}
}

void result_compare(char player, char opponent) {
	if (player == opponent) {
		show_result(RESULT_TIE);
	}
	
	else if (player == PAPER) {
		if (opponent == ROCK) {
			show_result(RESULT_WIN);
		}
		else if (opponent == SCISSORS) {
			show_result(RESULT_LOSE);
		}
	}
	else if (player == ROCK) {
		if (opponent == SCISSORS) {
			show_result(RESULT_WIN);
		}
		else if (opponent == PAPER) {
			show_result(RESULT_LOSE);
		}
	}
	
	else if (player == SCISSORS) {
		if (opponent == PAPER) {
			show_result(RESULT_WIN);
		}
		else if (opponent == ROCK) {
			show_result(RESULT_LOSE);
		}
	}
	
}

static void menu_update(void)
{
	if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
		choosing();
	}
}

static void game_update(void)
{
	switch (currentState)
	{
		case MENU:
			menu_update();
			break;
	}
}

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
	
	task* tasks[] =
	{
		init_navswitch_controller(),
		init_display_controller(),
		init_led_controller(),
		init_game(),
		NULL
	};
	
    start();
	scheduler_init(tasks);
}
