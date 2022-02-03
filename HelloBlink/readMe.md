## Hello-Blink

Shows an example of toggling PORTB1 (PB1) bit of PORTB register of the atmega328p chip on the arduino nano IC using AVR-Core libs from Atmel Corp.

### Example 2 : 
- Blinks the LED on PB0 or D9 bit of PORTB register.
- Idea : 
    - Since, `PORTB1 = 0b00000010`, then to switch it on, simply we `flip all the bits on register B` and then `AND` the result with the `PORTB1` :
    ```c
    PORTB1 = 0b000000010;
    PORTB = ~PORTB & PORTB1;
    ```
    - Now, we could do one more step to toggle the PB1 bit `POWER` selectively, which is `ANDING` the `PORTB1` with either `0xFF` which is `HIGH` or `0x00` which is `LOW` :
    ```c
     #define HIGH 0xFF
     #define LOW 0x00
     
     PORTB1 = 0b000000010;
     POWER = HIGH;
     PORTB = ~PORTB & (PORTB1 & POWER);
     ```
- The code based on this circuit : 
https://github.com/Scrappers-glitch/AVR-Sandbox/blob/master/HelloBlink/fritzing/Blink%20LED_bb.png


