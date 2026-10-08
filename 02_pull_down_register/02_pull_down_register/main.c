/*
 * 02_pull_down_register.c
 *
 * Created: 07-10-2026 18:51:56
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRD &= ~(1<<DDD5);
	DDRB |= (1<<DDB5);
    while (1) 
    {
		if (PIND & (1<<PIND5))
		{
			PORTB |= (1<<PORTB5);
		}
		else
		{
			PORTB &= ~(1<<PORTB5);
		}
    }
}

