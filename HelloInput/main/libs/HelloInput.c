#include<avr/io.h>
#include<util/delay.h>
/**
 * Blink on PORTB1 (PB1) or D9
 */
#define LOW 0
#define HIGH 1

int main(void) {
 PORTB=0x00;
 for(;;) {
        PB1* p =new PB1; 
	_delay_ms(1000);

	_delay_ms(1000);
 }
 return 0;
}

