/*
 * GPIOs_Part1_C.c
 *
 * Created: 3/2/2019 4:46:15 PM
 * Author : Benjamin Johnson
  * Student #: 5003284489
  * Email: johnsb18@unlv.nevada.edu
  */

  #define F_CPU 16000000UL

  #include <avr/io.h>
  #include <util/delay.h>


int main(void)
{
    DDRB |= (1<<2);		// set PORTB.2 for output
	
    while (1) 
    {
		_delay_ms(435);		// delay for 60% DC
		PORTB &= ~(1<<2);	// set LED on
		_delay_ms(290);		// delay for remaining 40%
		PORTB |= (1<<2);	// set LED off
    }
}

