#include "communication.h"
#include "ir_serial.h"

void communication_initialise(void)
{
	ir_serial_init();
}
void send_type(char type)
{
	if (type == ROCK || type == SCISSORS || type == PAPER)
		ir_serial_transmit(type);
}
void send_confirmation(void)
{
	ir_serial_transmit('X');
}
Result get_result(void)
{
	uint8_t data;
	ir_serial_ret_t result = ir_serial_receive(&data);
	if (result != IR_SERIAL_OK)
		return RESULT_NONE;
		
	switch (data)
	{
		case ROCK:
			return RESULT_ROCK;
		case SCISSORS:
			return RESULT_SCISSORS;
		case PAPER:
			return RESULT_PAPER;
		default:
			return RESULT_NONE;
	}
}
