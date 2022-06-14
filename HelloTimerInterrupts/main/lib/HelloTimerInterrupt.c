/**
 * @file HelloTimerInterrupt.c
 * @author pavl_g
 * @brief A simple example demonstrating the usage of a timer vector Interrupt Service Routine.
 * @version 0.1
 * @date 2022-06-14
 * 
 * @copyright Copyright (c) Scrappers 2022
 * 
 */
#include<avr/io.h>
#include<util/delay.h>
#include<Digital.h>
#include<avr/interrupt.h>

void blink(volatile uint8_t&, const uint8_t&);

ISR(TIMER0_OVF_vect) {
   TCNT0 = 0x00; // reset the counter
   blink(PORTB, PIN_5);
}

int main(void) {
   
   resetPort(PORTB);

   TCNT0 = 0xFF; // reset timer value
   TCCR0B = 0x01; // normal mode

   TIMSK0 = (1 << TOIE0); // enable Timer0 overflow interrupt
         
   sei(); // set enable interrupt -- exiting the current block and entering the next interrupt

   while (1); // keep the program busy !

 return 0;
}

void blink(volatile uint8_t& PORT, const uint8_t& PIN) {
   // keep blinking a pin
   digitalWrite(PORT, PIN, LOW);
   _delay_ms(1000);
   digitalWrite(PORT, PIN, HIGH);
   _delay_ms(1000);
}
