#include<avr/io.h>
#include<util/delay.h>
#include<string.h>


volatile uint8_t analogValue[2];

void usart_init(void) {
	UCSR0B = 0b00001000; // TXEN_BIT = 1, enables the transmitter buffer register.
	UCSR0C = 0b10000110; // enables the UCSZ0, UCSZ1 and URSEL
	UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

void usart_send(uint8_t character) {
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = character;
}

void adc_init(void) {
	DDRC = 0x00; 
	PORTC = 0xFF;
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    ADMUX = (1<<REFS0); // AVCC = VCC and ADC0 select		
}

void start_adc() {
	while(1) {
		ADCSRA |= (1 << ADSC);
		while ((ADCSRA & (1<<ADIF)) == 0);
		_delay_ms(500);
		PORTB = ADCH;
	}
}

int main(void) {
	usart_init();
	adc_init();
	start_adc();
	usart_send(analogValue[0]);
	usart_send(analogValue[1]);
return 0;
}



