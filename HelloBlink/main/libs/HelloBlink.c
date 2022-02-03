/**
 * Blinks an LED at D9 or PB1.
 * 
 * @file HelloBlink.c
 * @author pavl_g.
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<avr/io.h>
#include<util/delay.h>
#include<Digital.h>

int main(void) {
  resetPin(PORTB, PIN_1);
 for(;;) {
    digitalWrite(PORTB, PIN_1, HIGH);
    _delay_ms(1000);
    digitalWrite(PORTB, PIN_1, LOW);
    _delay_ms(1000);
 }
 return 0;
}


