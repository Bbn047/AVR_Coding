/*
 * 14_external_nterrupt_modular.c
 *
 * Created: 04-11-2026 21:16:46
 * Author : bibin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //used when using interrupts

#include "external_interrupt.h"
#include "gpio.h"


int main(void)
{
    gpio_init();
	external_interrupt_INT0_init();
    while (1) 
    {
    }
}

