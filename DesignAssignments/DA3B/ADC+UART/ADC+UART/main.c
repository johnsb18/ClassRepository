/*
 * ADC+UART.c
 *
 * Created: 3/31/2019 3:46:57 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALER (F_CPU /BAUDRATE/16 - 1)

void USART_init(unsigned int ubrr);
void ADC_init(void);
void read_ADC (void);
void USART_tx_string(char *data);

volatile unsigned int ADC_temp;
char outs[20];

int main(void)
{
	ADC_init();							// initialize ADC
	USART_init(BAUD_PRESCALER);			// initialize analog to digital
	USART_tx_string("Connected!\r\n");	// program working so far
	_delay_ms(125);						// some delay before starting
	

	sei();								// enable interrupts
	
    while (1) {};						// wait for interrupt
}

ISR (TIMER1_OVF_vect)
{
	read_ADC();							// read ADC
	snprintf(outs,sizeof(outs),"3f\r\n", ADC_temp); // print float
	USART_tx_string(outs);				// output to terminal
	TCNT1 = 49911;						// reset timer
}

void USART_init (unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0C = (1 << TXEN0);				// enable Rx, TX & Rx interrupt
	UCSR0B = (3 << UCSZ00);				// asynchronous 8 N 1
}

void ADC_init (void)
{
	ADMUX = (0<<REFS1)|					// reference selection bits
	(1<<REFS0)|							// AVcc - external cap at AREF
	(0<<ADLAR)|							// ADC Left Adjust Result
	(1<<MUX2)|							// Analog Channel Selection Bits
	(0<<MUX1)|							// ADC0 (PC0 PIN23)
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|					// ADC Enable
	(0<<ADSC)|							// ADC Start Conversion
	(0<<ADATE)|							// ADC Auto Trigger Enable
	(0<<ADIF)|							// ADC Interrupt Flag
	(0<<ADIE)|							// ADC Interrupt Enable
	(1<<ADPS2)|							// ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
	
		TCCR1B |= (1<<CS12) | (1<<CS10);	// prescaler = 1024
		TIMSK1 = (1<<TOIE1);				// enable overflow flag
		TCNT1 = 49911;						// reset timer (65535 - 15624)
}

void read_ADC (void)						// read ADC pins
{
	unsigned char i=4;
	ADC_temp = 0;
	while (i--){
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		ADC_temp += ADC;
		_delay_ms(50);
	}
	ADC_temp = (ADC_temp / 4);				// average a few samples
}

void USART_tx_string (char *data)
{
	while ((*data != '\0')){
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = *data;
		data++;
	}
}