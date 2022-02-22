#include<avr/io.h>
#include<util/delay.h>

void powerPin(volatile uint8_t&, const uint8_t&);

int main(void) {
	while (true) {
		if (PORTB5 & 0b00100000) {
			powerPin(PORTB, PORTB5);
		}
	}
return 0;
}
void powerPin(volatile uint8_t& PORT, const uint8_t& PIN) {
    PORT = PORT | PIN;
}
