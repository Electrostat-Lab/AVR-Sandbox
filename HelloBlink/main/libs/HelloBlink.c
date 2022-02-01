#include<avr/io.h>
#include<util/delay.h>
/**
 * Blink on PORTB1 (PB1) or D9
 */
#define PORTB1_ON 0b0000010
#define PORTB1_OFF 0b00000000
#define LOW 0x00
#define HIGH 0xFF

void digitalWrite(volatile uint8_t&, unsigned char PIN, unsigned char POWER);

int main(void) {
 PORTB=0x00;
 for(;;) {
	digitalWrite(PORTB, PORTB1_ON, HIGH);
	_delay_ms(1000);
	digitalWrite(PORTB, PORTB1_ON, LOW);
	_delay_ms(1000);
 }
 return 0;
}

void digitalWrite(volatile uint8_t& PORT, unsigned char PIN, unsigned char POWER) {
  // 1) flip all the port bits
  // then pass the bits to an and gate with the powered pin
  // if the powered pin has all its bits turned to 1 then the result that all bits would be turncated to 1
  // so, only the true bits (the bits that equals to 1) on both sides of AND would be activated.
  PORT = ~PORT & (PIN & POWER);
}
