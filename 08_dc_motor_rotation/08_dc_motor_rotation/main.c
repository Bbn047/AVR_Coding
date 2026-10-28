/*
 * 08_dc_motor_rotation.c
 *
 * Created: 29-10-2026 00:08:00
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void dc_motor_init()
{
	//config portD pin 1,2 and 3 as input
	DDRD |= ((1<<DDD2) | (1<<DDD2) | (1<<DDD3));
	//enable pin stay high
	PORTD |= (1<<PORTD3);
}


void forward_rotation(){
	//forward rotation
	PORTB |= (1<<PORTD1);
	PORTD &= ~(1<<PORTD2);
}

void stop_rotate(){
	//stop rotation
	PORTD &= ~((1<<PORTD1) | (1<<PORTD2));
}

void backward_rotation(){
	//forward rotation
	PORTB |= (1<<PORTD2);
	PORTD &= ~(1<<PORTD1);
}
int main(void)
{
    dc_motor_init();
    while (1) 
    {
		//forward rotation 
		forward_rotation();
		_delay_ms(3000);  // 3 sec
		
		stop_rotate();
		_delay_ms(1000); // 1 sec
		
		backward_rotation();
		_delay_ms(3000);
    }
}

