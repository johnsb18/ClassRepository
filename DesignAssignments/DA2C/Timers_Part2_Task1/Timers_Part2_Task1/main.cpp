/*
 * Timers_Part2_Task1.cpp
 *
 * Created: 3/23/2019 1:55:00 PM
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
	TCCR0A = 0;							// normal operation
	TCCR0B |= (1<<CS02) | (1<<CS00);	// prescaler = 1024
	TCNT0 = 4;							// timer value for .725 sec
	TIMSK0 = (1<<TOIE0);				// enable timer0 overflow interrupt
	sei();								// enable interrupts
	
	
    while (1) {		// wait for timer interrupt
    }
}

ISR (TIMER0_OVF_vect)
{
	OVFCOUNT++;			// increment counter
	if (OVFCOUNT == OVFLIMIT) {
		PORTB ^= (1<<2);		// toggle LED
		if(OVFLIMIT == 18) {
			OVFLIMIT = 27;		// set ovf limit for 60% of DC
		} else {
			OVFLIMIT = 18;		// set ovf limit for 40% of DC
		}
		OVFCOUNT = 0;			// reset counter
	}
	TCNT0 = 4;			// timer value for .725 sec
}