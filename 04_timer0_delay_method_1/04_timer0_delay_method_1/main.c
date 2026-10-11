/*
 * 04_timer0_delay_normal_mode_method_1.c
 *
 * Created: 11-10-2026 01:14:40
 * Author : bibin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#define LED PORTD5
void timer0_init()
{
	// step 1: configure timer0 in Normal mode
	TCCR0A &= ~((1<<WGM00) | (1<<WGM01));
	
	/*-----------------calculation----------------
	 clock frequency (F_CPU)  : 16 MHz (16000000)
	 prescalar value : 1024;
	 F-Timer = 16000000 /1024
	         = 15625 HZ
	Time period : 1 / frequency - 1 / timer frequency (timer)
	            = 1 / (16000000 / 1024)
				= 1 / 15625
				= 0.000064
				= 64 microseconds
	Time taken for tick is 64 microseconds, therefore time taken for 1 overflow  = time taken for 1 tick * total no.of icks
	time for 1 overflow = 64 * 256
	                    = 16.384 ms (microseconds)
	1 second - 1000 milliseconds
	there for  1 second = 1000/ 16.384
	                     = 61.0351 ~ 61
	*/
	
	//configuring prescalar value as 1024
	TCCR0B |= ((1 << CS02) | (1 << CS00));
}

void delay_1sec()
{
	for(uint8_t i = 0; i <= 61; ++i)
	{
		//checking if TOV0 (overflow flag bit) is set
		while(!(TIFR0 & (1 << TOV0)));  // waiting for overflow
		
		//clearing he TOV using by writing 1 to it
		TIFR0 |= (1 << TOV0);  //cleared  the bit
	}	
}


int main(void)
{
    timer0_init();
	DDRB |= (1<<DDB5) ;//configuring port pin 5 as output
    while (1) 
    {
		PORTB ^= (1<<LED);  //LED => PORTB5
		delay_1sec();
    }
}

