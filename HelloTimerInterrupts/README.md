## Hello-Interrupts

A simple example demonstrating LED blinking on pin-5 on PORTB using a timer interrupt event handler, the handler invokes an interrupt service subroutine block in synchronization with the timer clock, the current clock state is provided through the `TCNT0` 8-bit register, the `TIMSK0` 8-bit registers enable the timers interrupt subroutine events bus.

1) Interrupt Service subroutine: A block of code to be executed using an interrupt service routine as an event handled in sync with an action clock.

Example: 
```c
ISR(TIMER0_OVF_vect) {
   blink(PORTB, PIN_5);
}
```

2) TCNT0: Timer0 counter register, a 16-bit arbitrary value representing 2 registers `TCNT1H` the highest 8-bit and the `TCNT1L` the lowest 8-bit that records the timer0 clock counts and signifies for an overflow event by setting the flag `TOV0` (Timer0 overflow), you can set a start for this or just use zero.

3) TIMSK0: Timer mask register, selects which timer ISR to activate, you can use multiple timers ISRs at the same time too, for more see issue #76.

Example: 
```c
TIMSK0 = (1 << TOIE0); // enable Timer0 overflow interrupt
```

4) TCCR0: Timer0 control register, used to set the mode for this timer.

NB: Other Timers information will be discovered after this issue #76.
