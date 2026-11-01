/*
 * 11_timer0_interrupt_nomal_mode.c
 *
 * Created: 01-11-2026 11:00:08
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>  //must be used when using the interrupt

volatile uint16_t overflow_count = 0;

ISR(TIMER0_OVF_vect)
{
	overflow_count ++; //count increases until reach limit(here 977)
	if (overflow_count >>= 977) // over low complete reset the count
	{
		PORTB ^= (1<<PORTB5);
		overflow_count = 0; //reseting overflow_count for tracking next overflow
	}
}

void timer0_interrupt_init()
{
	//load TCNT0 with 0
	TCNT0 = 0;
	
	//config timer0 in normal mode
	TCCR0A &= ~((1<<WGM00) | (1<<WGM01));
	
	//config prescalar value as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00));
	TCCR0B &= ~(1<<CS02);
	
	/*------------------calculation------------------
	f_cpu      = 16 000 000 hz
	prescalar  = 64
	f_timer    = f_cpu / prescalar
	           = 16 000 000 / 64
			   = 2 50 000
			   = 250 mhz
	t_tick     = 1 / f_timer
	           = 1 / 2 50 000
			   = 0.000004 - 4 us
			   
	overflow time  = total overflow * t_tick
	               = 256 * 4 us
				   = 1.024 ms
	overflow 1 sec => 1000 ms
	               = 1000 / 1.024 ms  _>interrupt trriger after each over flow
				   = 976.56 =>977 0verflows(rounded number)		   
	*/
	
	//step 3: choosing overflow interrupt
	TIMSK0 |= (1<<TOIE0);
}
	
void gpio_init()
{
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
}	
	
int main(void)
{
	sei();
	gpio_init();
	timer0_interrupt_init();
    while (1) 
    {
    }
}

