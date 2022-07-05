#include<avr/io.h>
#include<string.h>

#include<Serial.h>

const char* word = "hello\n";

Serial::UART* uart = Serial::UART::getInstance();

int main(void) {
	 uart->startProtocol(BAUD_RATE_57600);
	 uart->sprintln((char*) word);
 return 0;
}