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
	
	/**
	 * Digitally writes [HIGH] or [LOW] to a pin on a register.
	 * 
	 * @param PORT the register port ID.
	 * @param PIN the bin ID in binaries.
	 * @param POWER trigger the power, either HIGH or LOW.
	 */
	void digitalWrite(volatile uint8_t& PORT, unsigned char PIN, const int& POWER);

	/**
	 * Resets the specified port, the port is in unsigned 8-bit integer.
	 * 
	 * An avr register represents a PORT with 8 pins.
	 * 
	 * @param PORT the port to reset.
	 */
	void resetPort(volatile uint8_t& PORT);

	/**
	 * Resets a bit in a register to zero.
	 * 
	 * The register is a voltaile memory, but the pin is a const memory 
	 * as compared to its holder.
	 * 
	 * @param PORT a port representing the holder of the pin.
	 * @param PIN the pin to trigger representing a bit in the register.
	 */
	void resetPin(volatile uint8_t& PORT, const uint8_t& PIN);
	
	/**
	 * Powers on a bit in a port.
	 * 
	 * The PORT is a voltaile memory, while the bit is a const
	 * memory compared to the port whenever the port is active
	 * the pin has its state as constant.
	 * 
	 * @param PORT a port representing the holder of the pin.
	 * @param PIN the pin to trigger representing a bit in the register.
	 */
	void powerPin(volatile uint8_t& PORT, const uint8_t& PIN);
#endif
