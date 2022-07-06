/**
 * @file HelloUART.c
 * @author pavl_g.
 * @brief Shows a basic implementation of the [Serial.h] library.
 * @version 0.1
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<avr/io.h>
#include<string.h>

#include<Serial.h>

const char* message = "Data Transmission completed successfully !";

void Serial::UART::onDataReceiveCompleted(const uint8_t& data) {
	Serial::UART::getInstance()->println((const uint8_t) data, 10);
}

void Serial::UART::onDataTransmitCompleted(const uint8_t& data) {
	Serial::UART::getInstance()->sprintln((char*) message);
}

int main(void) {
	 Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600);
	 while (true); // wait forever
 return 0;
}