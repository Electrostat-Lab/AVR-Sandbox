/**
 * @file HelloBlink.c
 * @author your name (you@domain.com)
 * @brief Blinks an LED.
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
 resetPort(PORTB);
 for(;;) {
    digitalWrite(PORTB, PIN_1, HIGH);
    _delay_ms(1000);
    digitalWrite(PORTB, PIN_1, LOW);
    _delay_ms(1000);
 }
 return 0;
}


