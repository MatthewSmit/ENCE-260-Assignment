#include <avr/io.h>
#include "pacer.h"

#define TIMER_CLOCK_DIVISOR 64
#define TIMER_RATE (F_CPU / TIMER_CLOCK_DIVISOR)

static uint16_t rate;

void pacer_init(uint16_t hz)
{
	TCCR1A = 0;
	TCCR1B = 3;
	TCCR1C = 0;
	TCNT1 = 0;
	
	rate = TIMER_RATE / hz;
}

void pacer_wait()
{
	while (TCNT1 < rate)
	{
	}
	
	TCNT1 = 0;
}

void pacer_wait_ms(uint16_t ms)
{
	for (uint16_t i = 0; i < ms; i++)
		pacer_wait();
}
