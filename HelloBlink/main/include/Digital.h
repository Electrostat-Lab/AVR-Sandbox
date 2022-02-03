/**
 * Digitally triggers a bit in a register.
 * 
 * @file Digital.h
 * @author pavl_g.
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef DIGITAL
#define DIGITAL 1
	
	#include<avr/io.h>
	#define PIN_0 (0x01)
	#define PIN_1 (PIN_0 << PIN_0)
	#define PIN_2 (PIN_1 << PIN_0)
	#define PIN_3 (PIN_2 << PIN_0)
	#define PIN_4 (PIN_3 << PIN_0)
	#define PIN_5 (PIN_4 << PIN_0)
	#define PIN_6 (PIN_5 << PIN_0)
	#define PIN_7 (PIN_6 << PIN_0)
	#define LOW 0x00
	#define HIGH 0xFF

	void digitalWrite(volatile uint8_t&, unsigned char PIN, unsigned char POWER);
	void resetPort(volatile uint8_t& PORT);
#endif
