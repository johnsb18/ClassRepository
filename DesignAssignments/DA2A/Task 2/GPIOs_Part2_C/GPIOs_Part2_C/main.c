/*
 * GPIOs_Part2_C.c
 *
 * Created: 3/2/2019 2:56:16 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

 #define F_CPU 16000000UL

 #include <avr/io.h>
 #include <util/delay.h>

 int main(void)
 {
	DDRC &= (0<<2);		// connect PORTC.2 to switch as input
	PORTC |= (1<<2);	// enable pull-up
 
	DDRB |= (1<<2);		// set PORTB.2 for output (LED)
 
	while(1){
		if(!(PINC & (1<<PINC2))){	// check if pin is low
			PORTB &= ~(1<<2);		// set LED on
			_delay_ms(1250);		// set delay of 1.25 sec
		}
		else{						// otherwise (pin is high)
			PORTB |= (1<<2);		// set LED off
		}
	}
	return 0;
 }