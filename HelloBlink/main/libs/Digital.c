/**
 * Digitally triggers a bit in a register.
 * 
 * @file Digital.c
 * @author pavl_g.
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<Digital.h>

volatile uint8_t cache;

void resetPort(volatile uint8_t& PORT) {
    PORT = 0x00;
}

void resetPin(volatile uint8_t& PORT, const uint8_t& PIN) {
    PORT = PORT & (~PIN);
}

void powerPin(volatile uint8_t& PORT, const uint8_t& PIN) {
    PORT = PORT | PIN;
}

void digitalWrite(volatile uint8_t& PORT, unsigned char PIN, const int& POWER) {
  // assign the port to a powered pin
  // if power = HIGH, then the bit is activated.
  // if power = LOW, then the bit is de-activated.
  if (POWER == LOW) {
      resetPin(PORT, PIN);
  } else {
      powerPin(PORT, PIN);
  }
}