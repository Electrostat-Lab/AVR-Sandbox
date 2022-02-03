## Hello-Blink

Shows an example of toggling PORTB1 (PB1) bit of PORTB register of the atmega328p chip on the arduino nano IC using AVR-Core libs from Atmel Corp.

### Example 2 : 
- Blinks the LED on PB0 or D9 bit of PORTB register.
- Idea : 
    - 2 methods to consider : 
	```c
	void resetPin(volatile uint8_t& PORT, const uint8_t& PIN) {
	    PORT = PORT & (~PIN);
	}

	void powerPin(volatile uint8_t& PORT, const uint8_t& PIN) {
	    PORT = PORT | PIN;
	}
	```
	- `resetPin()` : resets the selected bit in a register to zero by flipping all the other bits then
	   `ANDING` the result with the current `PORT` values, this makes sure that we don't override or 		    change the other bits when altering a specific bit.
	- `powerPin()` : powers the selected bit in a register by `ORING` the bit with the `PORT`, so if the 	        bit is ZERO, its now on and if other bits are ONE they would stay ONE.
- The code based on this circuit : 
<img src="https://github.com/Scrappers-glitch/AVR-Sandbox/blob/master/HelloBlink/fritzing/Blink%20LED_bb.png">



