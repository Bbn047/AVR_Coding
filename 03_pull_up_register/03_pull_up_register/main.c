/*
 * 03_pull_up_register.c
 *
 * Created: 09-10-2026 01:18:19
 * Author : bibin
 */ 

#define  F_CPU = 16000000UL
#include <avr/io.h>


int main(void)
{
	DDRD &= ~(1<<DDD5);
	DDRB |= (1<<DDB5);
	while (1)
	{
		if (!(PIND & (1<<PIND5)))
		{
			PORTB |= (1<<PORTB5);
		}
		else
		{
			PORTB &= ~(1<<PORTB5);
		}
	}
}
