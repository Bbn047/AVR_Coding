/*
 * 07_timer0_CTC_mode-2.c
 *
 * Created: 28-10-2026 23:12:33
 * Author : bibin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void timer0_noraml_mode_init()
{
	// step 1: config timer0 in normal mode
	TCCR0A &= ~((1<<WGM00) | (1<<WGM01));
	
	//CALCULATING the value to be loaded into TCNT0 register and prescalar value
	
	/* step 2 : -----------calculation------------------------
	   F_CPU  = 16 000 000 MHZ  : 16 * 10^6
	   prescalar value = 64
	   F_timer = F_CPU / prescalar value
	           = 16 000 000 / 64
			   = 2 50 000
			   = 250 KHZ
	  time required for 1 tick = 1 / F_time
	           = 1 / 250
			   = 0.000001
			   = 4 * 10^-6
			   = 4 microseconds (us)
	  target delay = 1 ms -> 1000 us
	  number of ticks required for 1 ms = 1000/ 4 = 250 ticks
	  value to be loaded into TCNT0 register = total number of ticks - number of ticks required
	                                         = 256 - 250
											 = 6
	*/
	// step 3: load the value to TCNT0
	TCNT0 = 6;
	//step 4: choose prescalar value of 64
	TCCR0B |= ((1<<CS01) | (1<<CS00));
	TCCR0B &= ~(1<<CS02);
}

void delay_1sec()
{
	for(uint16_t i = 0; 1<1000; ++i)
	{
		//loading TCNT0 with 6 to start the count from 06 after each over
		TCNT0 = 6;
		//clearing the overflow flag by writing logic 1 into it 
		TIFR0 |= (1<<TOV0);
		//waiting  until the overflow happen
		while(!(TIFR0) & (1<<TOV0));
		
	}
}

int main(void)
{
    timer0_noraml_mode_init();
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		delay_1sec();
    }
}

