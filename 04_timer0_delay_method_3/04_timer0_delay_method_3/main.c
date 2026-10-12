/*
 * 04_timer0_delay_method_3.c
 *
 * Created: 13-10-2026 00:00:32
 * Author : bibin
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#define LED PORTB5

void timer0_init()
{
	TCCR0A &= ~((1<<WGM00) | (1<<WGM01));
	
	/*-------------------------calculation---------------
	  prescalar = 8
	  clock frequency = 16000000
	  f-Timer = 16000000 / 8
	          = 2000000 HZ 
	  time period = 1 / 2000000
	              = 0.0000005  => 0.5 micro seconds
	  timefor  over flow = 0.5 * 256
	                     = 128 microsecond
	  1 second = 1000 milliseconds
      1 sec = 10000 / 128
	        = 7812.5 ~ 7813
	*/
	
	TCCR0B |= (1<<CS01); // clk 8
}

void delay_1sec()
{
	for (uint8_t i=0; i<=7813; ++i)
	{
		//checking if TOV0 is set
		while (!(TIFR0 &(1<<TOV0)));
		
		// clear the TOV 
		TIFR0 &= ~(1<<TOV0); 
	}
}

int main(void)
{
    timer0_init();
	DDRB |= (1<<DDB5);  // set port b pin 5 output
	
    while (1) 
    {
		PORTB ^=(1<<LED);
		delay_1sec();
    }
}

