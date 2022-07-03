#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#include<Serial.h>

int main(void) {

	Serial::UART* uart = (Serial::UART*) calloc(1, sizeof(Serial::UART*));
	uart->startProtocol();
	while (true) {
		uint8_t read = uart->read() - '0'; /* convert from ASCII representation to Decimal */
		uart->println(read, 10);
	}
	

	return 0;
}



