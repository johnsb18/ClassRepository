/*
 * Step Serv Motors.c
 *
 * Created: 4/22/2019 4:32:32 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRD = 0x0F;								// PORTD lower pins are output
	TCCR1A |= (1<<WGM01);						// CTC mode
	TCCR1B |= (1<<WGM12)|(1<< CS12)|(1<<CS10);	// prescaler = 1024
	
	ADMUX |= (1<<REFS0);				// use ref voltage at Aref
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
    while (1)		// timer set for .1 second (65536 - 1562)
	{
		while ((ADCSRA & (1<<ADIF)) == 0);	// process ADC
		OCR1A = ADC;				// set new limit
		
		TCNT1 = 0;					// reset timer
		while (TCNT0 != OCR1A) {}	// delay
		PORTD = 0x09;				// rotate motor
		
		TCNT1 = 0;					// reset timer
		while (TCNT0 != OCR1A) {}	// delay
		PORTD = 0x03;				// rotate motor
		
		TCNT1 = 0;					// reset timer
		while (TCNT0 != OCR1A) {}	// delay
		PORTD = 0x06;				// rotate motor
			
		TCNT1 = 0;					// reset timer
		while (TCNT0 != OCR1A) {}	// delay
		PORTD = 0x0C;				// rotate motor
	}
}
