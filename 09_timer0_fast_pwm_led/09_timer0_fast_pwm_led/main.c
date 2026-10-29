/*
 * 09_timer0_fast_pwm_led.c
 *
 * Created: 29-10-2026 13:53:47
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

void timer0_fast_pwm_init()
{
	//step 1: config PDD as output  (OCR0A)
	DDRD|= (1<<DDD6);
	
	//config timer0 in fast PWM mode 
	TCCR0A|= ((1<<WGM00) | (1<<WGM01));
	/*---------calculation---------------
	F_pwm = F_CPU / prescalar value (N)
	      = f_cpu / (n * 256)   -> N is prescalar value  => fastpwm equation 
    F_CPU = 16 000 000
	N     = 64
	F_PWM = 16 000 000 / (64 * 256 )
	      = 976.5625 HZ => 1 KHZ
	
	*/
	
	//step 4: config prescalar  value as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00));
	TCCR0B &= ~(1<<CS02);
	
	//step 5: config non inverting mode
	TCCR0A |= (1<<COM0A1);
	
	//PWM value
	//OCR0A = 192;
}

int main(void)
{
    timer0_fast_pwm_init();
    while (1) 
    {
		//brightness increment
		for(uint8_t i=0; i<255; ++i)
		{
			OCR0A = i;
			_delay_ms(50);
		}
		
		//brightness decrement
		for(uint8_t i=255; i>0; --i)
		{
			OCR0A = i;
			_delay_ms(50);
		}
    }
}

