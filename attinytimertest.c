/*
 * attinytimertest.c
 *
 *  Created on: May 14, 2016
 *      Author: compi
 */
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdlib.h>


////////////////////////////////////////////////////////////////////
void setuptimers()
{
	TCCR0A = 0;						//t0: stop
	TCCR0B = 0;
	TCNT0 = 0;						//t0: reset counter

	TCCR1 = 0;						//t1: stop
	GTCCR |= _BV(PSR1);				//t1: prescaler reset
	TCNT1 = 0;						//t1: reset counter
	OCR1C = 124;					//for counter autoreset
	OCR1A = 124;					//for interrupt

	TIMSK = _BV(TOIE0) | _BV(OCIE1A);	//enable interrupts for t0 & t1

	TCCR0B = _BV(CS00) | _BV(CS01) | _BV(CS02);	//t0: ext clk rising edge
	TCCR1 |= _BV(CS13) | _BV(CTC1);	//t1: prescaler of 128
}

////////////////////////////////////////////////////////////////////
int main(void)
{
	DDRB |= _BV(PORTB1);

	setuptimers();
	sei();
	while(1)
	{
		_delay_ms(500);
	}
}

////////////////////////////////////////////////////////////////////
ISR (TIMER0_OVF_vect)
{
	static uint16_t	counter = 0;
	if(++counter >= 500 ) {
		counter = 0;
		PORTB ^= _BV(PORTB1);
	}
}
////////////////////////////////////////////////////////////////////
ISR (TIMER1_COMPA_vect)
{
	static uint16_t	counter = 0;
	if(++counter >= 500 ) {
		counter = 0;
		PORTB ^= _BV(PORTB1);
	}
}
