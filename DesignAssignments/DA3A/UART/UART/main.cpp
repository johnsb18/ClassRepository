/*
 * UART.cpp
 *
 * Created: 3/27/2019 3:31:10 PM
 * Author : Benjamin Johnson
 * Student #: 5003284489
 * Email: johnsb18@unlv.nevada.edu
 */

#define BAUD 9600
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/setbaud.h>


void USART_init(void);					// initializes analog to digital
void USART_tx_string(char*data);		// prints a string
void USART_tx_char (char integer);		// prints a character

char nextLine[] = "\n";					// declare next line string
volatile float usart_temp = 3.14;		// declare float
char outs[20];							// allocate memory space for float

int main(void)
{
    USART_init();						// initialize analog to digital
	
	TCCR1B |= (1<<CS12) | (1<<CS10);	// prescaler = 1024
	TIMSK1 = (1<<TOIE1);				// enable overflow flag
	TCNT1 = 49911;						// reset timer (65535 - 15624)
	sei();								// enable interrupts
	
    while (1) {}						// wait for timer interrupt
}

void USART_init (void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);	// enable RX and TX
}

ISR (TIMER1_OVF_vect)
{
	USART_tx_string(nextLine);				// next line
	USART_tx_string("This is working!");	// print string
	USART_tx_string(nextLine);				// next line
	USART_tx_char('3');						// print int
	USART_tx_string(nextLine);				// next line
	snprintf(outs, sizeof(outs), "%f\r\n", usart_temp);	// store float in outs
	USART_tx_string(outs);					// print float
	USART_tx_string(nextLine);				// next line
	
	TCNT1 = 49911;							// reset timer
}

void USART_tx_string (char*data)
{
	while ((*data != '\0')){			// iterate through entire string
		while (!(UCSR0A & (1<<UDRE0)));	// wait for UDRE0 flag to go high
		UDR0 = *data;					// set USART I/O data register to string
		data++;							// iterate through string
	}
}

void USART_tx_char (char integer)
{
	while (!(UCSR0A & (1<<UDRE0)));		// wait for UDRE0 flag to go high
	UDR0 = integer;					// set USART I/O data register to int as char
}