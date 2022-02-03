#include<Digital.h>

/**
 * Resets the specified port, the port is in unsigned 8-bit integer.
 * An avr register represents a PORT with 8 pins.
 * 
 * @param PORT the port to reset.
 */
void resetPort(volatile uint8_t& PORT) {
    PORT = 0x00;
}

/**
 * Digital writes [HIGH] or [LOW] to a pin on a register.
 * 
 * @param PORT the register port ID.
 * @param PIN the bin ID in binaries.
 * @param POWER trigger the power, either HIGH or LOW.
 */
void digitalWrite(volatile uint8_t& PORT, unsigned char PIN, unsigned char POWER) {
  // 1) flip all the port bits
  // then pass the bits to an and gate with the powered pin
  // if the powered pin has all its bits turned to 1 then the result that all bits would be turncated to 1
  // so, only the true bits (the bits that equals to 1) on both sides of AND would be activated.
  PORT = ~PORT & (PIN & POWER);
}