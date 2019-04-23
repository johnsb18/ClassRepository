/*
 * Servo Motor.c
 *
 * Created: 4/22/2019 6:20:52 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);	// non-inverted PWM
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);	// prescaler 64, mode 14 fast PWM
	DDRB = 0x02;								// set PB1 to output
	
	DDRD = 0x40;						// PD6 as output
	
	ADMUX |= (1<<REFS0);				// use ref voltage at Aref
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
    while (1) 
    {
		while ((ADCSRA & (1<<ADIF)) == 0);	// process ADC
		OCR1A = ADC;
    }
}

