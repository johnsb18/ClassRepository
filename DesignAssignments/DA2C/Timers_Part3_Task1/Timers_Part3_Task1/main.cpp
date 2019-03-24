/*
 * Timers_Part3_Task1.cpp
 *
 * Created: 3/23/2019 7:06:05 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t OVFCOUNT = 0;		// overflow count multiplier
uint8_t OVFLIMIT = 18;		// overflow count limit, set for 40% of DC

int main(void)
{
    DDRB |= (1<<2);						// set PORTB.2 for output (LED)
	PORTB |= (1<<2);					// set LED off
	OCR0A = 252;						// TOP = 256 - 4
	TCCR0B |= (1<<WGM02) | (1<<CS02) | (1<<CS00);	// prescaler = 1024, CTC mode
	TIMSK0 = (1<<OCIE0A);				// enable timer0 compare match int
	TCNT0 = 0;							// initialize timer to 0
	sei();								// enable interrupts
	
	
    while (1) {			// wait for interrupt
    }
}

ISR (TIMER0_COMPA_vect)
{
	OVFCOUNT++;		// increment counter
	if (OVFCOUNT == OVFLIMIT) {
		PORTB ^= (1<<2);		// toggle LED
		if(OVFLIMIT == 18) {
			OVFLIMIT = 27;		// set overflow limit for 40% DC
		} else {
			OVFLIMIT = 18;		// set overflow limit for 60% DC
		}
		OVFCOUNT = 0;		// reset counter
	}
	TCNT0 = 0;		// reset timer
}