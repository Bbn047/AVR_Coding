/*
 * external_interrupt.c
 *
 * Created: 04-11-2026 21:19:16
 *  Author: bibin
 */ 
#include "external_interrupt.h"
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	//toggle led connected to port b5
	PORTB ^= (1<<PORTB5);
}

void external_interrupt_INT0_init()
{
	//step 1: configuring / enabling INT0 as interrupt
	EIMSK |= (1<<INT0);
	//step 2: configuring pd2 as input for external interrupt
	DDRD &= ~(1<<DDD2);
	//step 3: configuring interrupt trigger : rising edge
	EICRA |= ((1<<ISC01) | (1<<ISC00));
	
	//step 4: enable global interrupt
	sei();
}