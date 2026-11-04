/*
 * 13_external_ interrupt.c
 *
 * Created: 04-11-2026 19:54:17
 * Author : bibin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	//toggle led when rest
	PORTB ^= (1<<PORTB5);
}

ISR(INT1_vect)
{
	//toggle led when rest
	PORTB ^= (1<<PORTB4);
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

void external_interrupt_INT1_init()
{
	//enabling INT1 as interrupt
	EIMSK |= (1<<INT1);
	//config pd3 as input for external interrupt
	DDRD &= ~(1<<DDD3);
	//config interrupt trigger : falling edge 
	EICRA |=(1<<ISC11);  //falling edge ISC10 => 1
	EICRA &= ~(1<<ISC10); //falling edge ISC10 => 0
	
	sei();
}

void gpio_init()
{
	//configure pb5 as output
	DDRB |= (1<<DDB5);
	//config pb4 as output
	DDRB |= (1<<DDB4);
}

int main(void)
{
	gpio_init();
   external_interrupt_INT0_init();
   external_interrupt_INT1_init();
    while (1) 
    {
    }
}

