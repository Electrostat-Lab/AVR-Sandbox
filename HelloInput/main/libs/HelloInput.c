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

void usart_init(void) {
	UCSRB = (1 << TXEN);
	UCSR1C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRRL = 0x33;
}

void usart_send(unsigned char character) {
	while (! (UCSRA & (1 << UDRE)));
	UDR = character;
}

int main(void) {
 usart_init();
 while (HIGH) {
	 usart_send('G');
 }
 
 return 0;
}

