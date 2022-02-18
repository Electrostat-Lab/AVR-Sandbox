#include<avr/io.h>
#include<util/delay.h>

#  define UDR     UDR0
#  define UCSRA   UCSR0A
#  define UCSRB   UCSR0B
#  define FE      FE0
#  define TXEN    TXEN0
#  define RXEN    RXEN0
#  define RXCIE   RXCIE0
#  define UDRE    UDRE0
#  define U2X     U2X0
#  define UBRRL   UBRR0L

/**
 * Blink on PORTB1 (PB1) or D9
 */
#define LOW 0
#define HIGH 1

const char* word = "hello\n";
int i = 0;

void usart_init(void) {
	UCSR0B = 0b00001000; // TXEN_BIT = 1, enables the transmitter buffer register.
	UCSR0C = 0b10000110; // enables the UCSZ0, UCSZ1 and URSEL
	UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

void usart_send(unsigned char character) {
	while (! (UCSR0A & (1 << UDRE)));
	UDR0 = character;
}

int main(void) {
 usart_init();
 while (i < 6) {
	 usart_send(word[i++]);	
 }
 return 0;
}

