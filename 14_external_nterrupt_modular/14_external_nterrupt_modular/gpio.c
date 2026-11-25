/*
 * gpio.c
 *
 * Created: 04-11-2026 21:28:04
 *  Author: bibin
 */ 

#include "gpio.h"

void gpio_init()
{
	//configure pb5 as output
	DDRB |= (1<<DDB5);
	PORTB &= ~(PORTB5);
}