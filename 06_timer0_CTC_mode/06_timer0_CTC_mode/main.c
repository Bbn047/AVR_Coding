/*
 * 06_timer0_CTC_mode.c
 *
 * Created: 14-10-2026 18:14:42
 * Author : bibin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void gpio_init()
{
	DDRB |=(1<<DDB5); // setting PORTB pin 5 as output
}

//timer0 initialization in CTC mode
void timer0_ctc_init()
{
	//step 1 : configuring timer0 in CTC mode wgm00=1, wgm01=1
	TCCR0A |= (1<<WGM01); 
	TCCR0A &= ~(1<<WGM00);
	 
	/*-----------CALCULATION-------------
	  F_CPU = 16 000 000
	  prescalar value = 64
	  F_Timer = 16 000 000/ 64
	          = 2 50 000
			  = 250 kHz
	  tick Period (1 tick) = 1 / F_timer
	                       = 1 / 250 kHz
						   = 0.000004
						   = 4 microseconds - 4uf
	  Target delay = 1 ms = 1000 us
	  required ticks      = (target delay / tick period) - 1
	                      = (1000 / 4) -1
						  = 249 ticks
	  
	*/
	
	//step 2: configuring prescalar value as 64
	TCCR0B |= ((1<<CS00) | (1<<CS01));
	TCCR0B &= ~(1<<CS02);
	
	//step 3: loading the calculated required ticks for 1 ms into OCR0A register
	OCR0A = 249;
}

void delay_1sec()
{
	for(uint16_t i=0; i<1000; ++i)
	{
		//waiting until the compare flag A is set
		while(!(TIFR0 & (1<<OCF0A)));
		//clearing the flag
		TIFR0 |= (1<<OCF0A); // cleared
	}
}

int main(void)
{
   gpio_init();
   timer0_ctc_init();
    while (1) 
    {
		//toggling the port B
		PORTB ^= (1<<PORTB5);
		delay_1sec();
    }
}

