/*
 * 15_adc_led_brightness_control.c
 *
 * Created: 26-11-2026 00:40:06
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void adc_init()
{
	//step 1: choosing reference voltage
	ADMUX |= (1<<REFS0);
	//choosing ADC channel (A0)
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
	//step 3: enabling ADC
	ADCSRA |= (1<<ADEN);
	/****************calculation***********************************************/
	/* F cpu = 16000000
	   prescalar  value  = 128
	   F_ADC = 16 000 000 / 128 = 125 kHz                                    */
	/************************************************************************/
	//step 4: configuring prescalar value of 128
	ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<ADPS0));
	
}

uint16_t read_adc()
{
	
	//step 1 : start the adc conversion
	ADCSRA |= (1<<ADSC);
	//waiting for conversion to end
	while(ADCSRA& (1<<ADSC)); 
	
	return ((ADCH<<8) | ADCL);
}

void pwm_init()
{
	
	//set pin D6(pd6 / OC0A) as output
	DDRD |= (1<<PD6);
	
	//config Timer 0 for fast pwm ( wgm01 = 1, wgm00 = 1)
	TCCR0A |= (1<<WGM01) | (1<<WGM00);
	//non- inverting mode on OC0A (COM0A1 =1, COM0A0 = 0
	TCCR0A |= (1<<COM0A1);
	
	//set prescalar value t0 64 (CS01= 1, CS001= 1) -> ~976HZ PWM frquency 
	TCCR0B |= (1<<CS01) | (1<<CS00);
}

int main(void)
{
 adc_init();
 pwm_init();
 
    while (1) 
    {
		uint16_t adc_vlaue= read_adc();
		//scaling down the 10 bit value into 8 bit value
		uint8_t pwn_duty= adc_vlaue >> 2;  // ADC_VALUE / 4 (2^2)
		OCR0A = pwn_duty; 
		
    }
}