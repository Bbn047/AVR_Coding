/*
 * 12_timer0_interrupt_ctc_mode.c
 *
 * Created: 04-11-2026 15:18:12
 * Author : bibin
 */ 

#define f_cpu 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> // used when using interrupt

volatile uint16_t overflow_count = 0;

void gpio_init()
{
	//config direction as output
	DDRB |= (1<<DDB5);
	//making it low during start
	PORTB &= ~(1<<PORTB5);
}

ISR(TIMER0_COMPA_vect)
{
	overflow_count++;
	if (overflow_count >=1000)
	{
		PORTB ^= (1<<PORTB5); // on-> off or off-> on
		overflow_count = 0; // reseting the overflow count
	}
	
}

void timer0_ctc_mode_init()
{
	//loading value at TCNT0 
	TCNT0 = 0;
	//step 1:
	TCCR0A |= (1<WGM01);
	TCCR0A &= ~(1<<WGM00);
	
	//step 2: calculation
	/*------------------------calculation----------------------------
	   f_cpu = 16 000 000 Hz
	   prescalar = 64
	   f_timer   = f_cpu / prescalar
	             = 16000 000 / 64
				 = 2 50 000 = 250 mhz
	   1 t_tick  = 1 / 250 000
	             = 4 us
	   required delay = 1ms => 100us
	   required tick = (required delay / t_ticks) - 1
	                 = 1000 / 4 
					 = 250 - 1
					 = 249 ticks
					 
	  overflow time  = total overflow * t_tick
	                 = 256 * 4 us
	                 = 1.024 ms
	  overflow 1 sec => 1000 ms
	                 = 1000 / 1.024 ms  _>interrupt trriger after each over flow
	                 = 976.56 =>977 0verflows(rounded number)
	 */
	
	//step 3: choose prescalar value as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00));
	TCCR0B &= ~(1<<CS02);
	
	//step 4: loading OCR0A  with required ticks
	OCR0A = 249;
	
	//step 4: enable compare match aA interrupt
	TIMSK0 |= (1<<OCIE0A);
}

int main(void)
{
	gpio_init();
	sei(); // global interrupt enable
    timer0_ctc_mode_init();
	
    while (1) 
    {
    }
}

