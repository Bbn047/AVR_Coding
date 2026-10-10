/*
 * 03_1_pull_up_register.c
 *
 * Created: 10-10-2026 12:34:52
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRD &=~(1<<DDD6);  // setting PORT D PIN 6 input
	DDRB |= (1<<DDB3);  // PORT B pIN 6OUTPUT
    while (1) 
    {
		if (!(PIND&(1<<PIND6)))  //hecking the PIND  register for switch press
		{
			PORTB ^=(1<<PORTB3);     // fliping the value 0 -> 1 ->0
			while(!(PIND&(1<<PIND6)));
			
		}
    }
}

