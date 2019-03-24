/*
 * Timers_Part1_Task1.cpp
 *
 * Created: 3/22/2019 6:17:48 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRB |= (1<<2);		// set PORTB.2 for output (LED)
	TCCR0A = 0;			// normal operation
	TCCR0B |= (1<<CS02) | (1<<CS00); // prescaler = 1024
	int count = 0;		// overflow counter
	
	
    while (1) {
		count = 0;					// reset counter
		TCNT0 = 0x00;				// reset timer
		while (count < 27){			// loop until 60% DC is met
			if(TCNT0 == 0xFF){		// if timer overflows
				count++;			// increment counter
				TCNT0 = 0x00;		// reset timer
			}
		}
		PORTB ^= (1<<2);			// toggle LED off
		count = 0;					// reset counter
		TCNT0 = 0x00;				// reset timer
		while (count < 18){			// loop until remaining 40% DC is met
			if(TCNT0 == 0xFF){		// if timer overflows
				count++;			// increment counter
				TCNT0 = 0x00;		// reset timer
			}
		}
		PORTB ^= (1<<2);			// toggle LED on
    }
}
