/*
 * 02_1_pull_down_register.c
 *
 * Created: 09-10-2026 00:10:08
 * Author : bibin
 */ 
#define F_CPU =16000000UL
#include <avr/io.h>
/* pull down register 
* toggle the led when each time press led 
*/

int main(void)
{
   DDRD &= ~(1<<DDD5); // port D pin 5 input
    DDRB |= (1<<DDB5);  // port B pin 5 output
    while (1) 
    {
		if (PIND & (1<<PIND5))  // checking switch press
		{
			PORTB ^= (1<<PORTB5);   // led on and off while pressing the push button each time
			while(PIND &= (1<<PIND5));  // checking the button is in pressed condition
		}
    }
}

