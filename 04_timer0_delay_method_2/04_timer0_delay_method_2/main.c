/*
 * 04_timer0_delay_method_2.c
 *
 * Created: 12-10-2026 22:44:02
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#define LED PORTB5

void timer0_init(){
	TCCR0A &= ~ ((1<<WGM00) | (1<<WGM01));
	
	/*-----------calculation---------------------\
	  clock frequency  (F_CPU) : 16 MHZ
	  prescalar value : 256;
	  F-timer = 16000000 / 256
	          =62500 HZ
	  Time period : 1 / frequency -1 / timer frequency (timer)
	              = 1 / 52500
				  = 0.000016
				  = 0.016 milliseconds
	  time taken for one tick is 0.016 milliseconds, therefore time taken for 1 overflow = time taken for 1 tick * total no.of ticks
	  time for 1 overflow = 0.016 * 256
	                      = 4.096 ms(micro seconds)
	  1 second --> 1000 milliseconds  
	  so 1 second = 1000 / 4.096
	              = 244.14 ~ 244
	*/
	
	TCCR0B |= (1<<CS02); //clk / 266
}

void delay_1Sec()
{
	for (uint8_t i = 0; i<=244; ++i)
	{
		//checking if TOV0 (overflow flag bit) is set
		while(!(TIFR0 & (1<<TOV0)));
		
		//clearing the TOV by written 1 to it
		TIFR0 |=(1<<TOV0);  // clear bit
	} 
}


int main(void)
{
    timer0_init();
	DDRB  |= (1<<DDB5); // port D pin 5 as input
    while (1) 
    {
		PORTB ^= (1<<LED); // LED => PORTB5
		delay_1Sec();
    }
}

