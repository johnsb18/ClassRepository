/*
 * Midterm_Project.c
 *
 * Created: 4/5/2019 3:21:18 PM
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
char outs[256];

char instr1[] = "AT";
char instr2[] = "AT+CWMODE=1";	// enables wifi
char instr3[] = "AT+CWLAP";	// list wireless AP in range
char instr4[] = "AT+CWJAP=\"AndroidAP\",\"easymode\""; // join network
char instr5[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80";
char instr6[] = "AT+CIPSEND=51 \\";
//unsigned char instr7[] = ("GET https://api.thingspeak.com/update?api_key=W6P5T8ZB7LDLGASQ&field1=%3d \r\n", ADC_temp);
char instr8[] = "AT+CIPCLOSE";

int main(void)
{
	ADC_init();							// initialize ADC
	USART_init(BAUD_PRESCALER);			// initialize analog to digital
	_delay_ms(125);						// some delay before starting
	TCNT1 = 49911;						// set timer

	sei();								// enable interrupts
	
	while (1) {};						// wait for interrupt
}

ISR (TIMER1_OVF_vect)
{
	USART_tx_string(instr1);
	_delay_ms(1000);
	USART_tx_string(instr2);
	_delay_ms(1000);
	USART_tx_string(instr3);
	_delay_ms(1000);
	USART_tx_string(instr4);
	_delay_ms(1000);
	USART_tx_string(instr5);
	_delay_ms(1000);
	USART_tx_string(instr6);
	_delay_ms(1000);
	//USART_tx_string(instr7);
	//_delay_ms(1000);
	USART_tx_string(instr8);
	_delay_ms(1000);
	
	
	read_ADC();							// read ADC
	snprintf(outs,sizeof(outs),"GET https://api.thingspeak.com/update?api_key=W6P5T8ZB7LDLGASQ&field1=%3d\r\n", ADC_temp); // print float
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
	(0<<MUX2)|							// Analog Channel Selection Bits
	(0<<MUX1)|							// ADC0 (PC2)
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
