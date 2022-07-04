/**
 * @file HelloAnalogRead.c
 * @author pavl_g.
 * @brief The entry point for testing the ADC and UART implementations where you can see what you trigger on the analog side.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define F_CPU 16000000UL /* set the software cpu frequency to max of the oscillator 16MHZ */

#include<avr/io.h>
#include<avr/interrupt.h>

#include<util/delay.h>
#include<string.h>

#include<Serial.h>
#include<Analog.h>

Serial::UART* uart = Serial::UART::getInstance();
Analog::Adc* adc = Analog::Adc::getInstance();

/**
 * @brief An interrupt service handler, fired when the ADC conversion completes.
 */
ISR(ADC_vect) { 
	uart->println(adc->analogRead(), 10);
	adc->startConversion(ADC_MUX0);
	_delay_ms(500);
}

/**
 * @brief The application main entry point.
 * 
 * @return int the application return exit state, 0 for GOOD, 1 for EXIT with error.
 */
int main(void) {
	
	uart->startProtocol(BAUD_RATE_57600);

	sei();

	adc->startProtocol();
	
	adc->startConversion(ADC_MUX0);

	while (1); // blocks the program here	

	return 0;
}