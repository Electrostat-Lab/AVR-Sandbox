#include<avr/io.h>
#include<util/delay.h>
#include<string.h>

const char* word = "hello\n";
int i = 0;

void usart_init(void) {
	UCSR0B = 0b00001000; // TXEN_BIT = 1, enables the transmitter buffer register.
	UCSR0C = 0b10000110; // enables the UCSZ0, UCSZ1 and URSEL
	UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

void usart_send(unsigned char character) {
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = character;
}

int main(void) {
	 usart_init();
	 while (i < strlen(word)) {
		 usart_send(word[i++]);	
	 }
 return 0;
}

