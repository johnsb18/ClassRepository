/*
 * PWM DC Motor.c
 *
 * Created: 4/10/2019 5:30:46 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int togMotor = 0;				// motor on/off toggle

int main(void)
{
	DDRD = 0x40;					// PD6 is output
	DDRC = 0x02;					// set PC0 as input, PC1 as output for interrupts, INT1 for interrupt
	PORTC |= (1<<1);				// enable pull-up
	TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);	// clear OC0A on compare match, fast PWM
	TCCR0B |= (1<<CS02)|(1<<CS00);					// prescaler = 1024
	PCICR |= (1<<PCIE1);			// enable pin change interrupt 1
	PCMSK1 |= (1<<PCINT9);			// enable pin change on PC1
	ADMUX |= (1<<REFS0);			// use ref voltage at Aref
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	sei();
	
    while (1) {	}		// run while waiting for interrupt
}

ISR (PCINT1_vect) {		// toggle interrupt
	if (!(PINC & (1<<PINC1))) {
		if (togMotor == 0) {	// turn motor off
			OCR0A = 0;
			PORTB &= ~(1<<PORTB2);
		}
		if (togMotor == 1) {	// turn motor on
			while ((ADCSRA & (1<<ADIF)) == 0);	// process ADC
			
			OCR0A = ADC;
			PORTB |= (1<<PORTB2);
		}
		_delay_ms(500);
		togMotor ^= 1;		// toggle motor control on/off
	}
}