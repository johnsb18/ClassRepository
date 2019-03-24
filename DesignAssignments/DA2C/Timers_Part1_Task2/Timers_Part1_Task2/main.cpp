/*
 * Timers_Part1_Task2.cpp
 *
 * Created: 3/23/2019 1:26:59 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRC &= (0<<2);		// connect PORTC.2 to switch as input
    PORTC |= (1<<2);	// enable pull-up
	DDRB |= (1<<2);		// set PORTB.2 for output (LED)
	TCCR0A = 0;			// normal operation
	TCCR0B |= (1<<CS02) | (1<<CS00); // prescaler = 1024
	int count = 0;		// overflow counter
	
	while (1) {
		if(!(PINC & (1<<PINC2))) {	// check if pin in low
			PORTB &= ~(1<<2);		// set LED on
			
			count = 0;				// reset counter
			TCNT0 = 0x00;			// reset timer
			while(count < 77) {		// loop until 1.25 sec delay met
				if(TCNT0 == 0xFF){	// if timer overflows
					count++;		// increment counter
					TCNT0 = 0x00;	// reset timer
				}
			}
		}
		else {
			PORTB |= (1<<2);		// set LED off
		}
    }
	return 0;
}

