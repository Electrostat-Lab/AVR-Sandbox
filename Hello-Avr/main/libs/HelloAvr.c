#include<avr/io.h>

int main(void) {
  // toggle all PORTB pins, 8 bits to 1
  uint8_t hello = 0xFF;
  PORTB = hello;
 return 0;
}
