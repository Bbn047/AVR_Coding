/*
 * GPIO_output.c
 *
 * Created: 07-10-2026 00:36:04
 * Author : bibin
 */ 

#define F_CPU 16000000UL //include the clock frequency

#include <avr/io.h>
#include <util/delay.h>  //for delay


int main(void)
{
   //setting the pin direction 

   DDRB |= (1<<DDB5); //configured PORTB pin 5 as output - using bitwise
   
    while (1) 
    {
		PORTB |= (1<<PORTB5);  //Making PORTB5 pin high
	_delay_ms(1000); //1000ms = 1s;
	PORTB &= ~(1<<PORTB5); // Making PORTB5 low
	_delay_ms(1000);
    }
}

