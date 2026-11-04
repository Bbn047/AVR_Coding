/*
 * 12_timer0_interrupt_ctc_mode_02.c
 *
 * Created: 04-11-2026 15:54:49
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile overflow_count;

void gpio_init()
{
	//config direction as output
	DDRB |= (1<<DDB5);
	//making it low during start
	PORTB &= ~(1<PORTB5);
}

ISR(TIMER0_COMPA_vect)
{
	overflow_count++;
	if (overflow_count >= 2000)
	{
		PORTB ^= (1<<PORTB5); // on=> off or off=> on
		overflow_count = 0;  // reset overflow count
	}
		
}

void timer0_interrupt_ctc_mode()
{
	//step 1: CTC mode select
	TCCR0A |= (1<<WGM01);
	TCCR0A &= ~(1<<WGM00);
	
	//step 2: calculation
	/*--------------calculation-------------------
	F_CPU     = 16 000 000 HZ
	prescalar = 64
	f_timer   = F_CPU / prescalar
	          = 16 000 000 / 64
			  = 2 50 000 => 250 mhz
	1 t_tick  = 1 / 2 50 000
	          = 4 us
	required delay = 2ms -> 2000us
	required ticks = (2000 / 4) - 1
	               = 500 - 1
				   = 499 ticks
	 */	
	//step 3: load value to TCNT0 
	TCNT0 = 0;
	
	//step 4: choose prescalar value as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00));
	TCCR0B &= ~(1<<CS02); 
	
	//step 5 : load OCR0A with required ticks
	OCR0A = 499;
	
	//step 5: enable compare match A interrupt
	TIMSK0 |= (1<<OCIE0A);
	
}

int main(void)
{
	gpio_init();
	sei(); //global interrupt enable
   timer0_interrupt_ctc_mode();
    while (1) 
    {
    }
}

