#include "system.h"
#include "display_controller.h"
#include "led_controller.h"
#include "scheduler.h"
#include "communication.h"
#include <stddef.h>

typedef enum {
	MENU,
	GAME_CHOOSING,
	GAME_WAITING,
	END
} State;

State currentState = Menu;

void start(void) {
	tinygl_text("< = >");
}

void choosing(void){
	/* use a number to determine choice*/
}

void show_result(int result) {
	if (result == 0) {
		tinygl_text("Tie");
	}
	
	if (result == 1) {
		tinygl_text("You Lose");
	}
	
	if (result == 2) {
		tinygl_text("You Win");
	}
	
}

void result_compare(char player, char opponent) {
	if (player == opponent) {
		show_result(0);
	}
	
	else if (player == PAPER) {
		if(opponent = ROCK) {
			show_result(2);
		}
		else if (opponent == SCISSORS) {
			show_result(1);
		}
	}
	else if (player == ROCK) {
		if(opponent = SCISSORS) {
			show_result(2);
		}
		else if (opponent == PAPER) {
			show_result(1);
		}
	}
	
	else if (player == SCISSORS) {
		if(opponent = PAPER) {
			show_result(2);
		}
		else if (opponent == ROCK) {
			show_result(1);
		}
	}
	
}

static void menu_update(void)
{
	if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
		choosing();
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
		init_navswitch(),
		init_display_controller(),
		init_led_controller(),
		init_game(),
		NULL
	};
	
    start();
	scheduler_init(tasks);
}
