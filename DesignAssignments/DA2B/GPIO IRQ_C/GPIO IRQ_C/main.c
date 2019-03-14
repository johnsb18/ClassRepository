/*
 * GPIO IRQ_C.c
 *
 * Created: 3/9/2019 1:50:27 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<2);		// set PORTB.2 for output (LED)
	PORTB |= (1<<2);	// set LED low
	DDRC &= (0<<2);		// connect PORTC.2 to switch as input
	PORTC |= (1<<2);	// enable pull-up
	EIMSK = (1<<INT0);	// enable external interrupt 0
	EICRA = (1<<ISC01);	// make INT0 falling edge triggered
	sei ();				// enable interrupts
	
    while (1) {}		// wait for interrupt
}

ISR (INT0_vect)	{		// ISR for external interrupt INT0
	PORTB ^= (1<<2);	// toggle PORTB.2 (LED)
	_delay_ms(1250);	// delay for 1.25 sec
}
