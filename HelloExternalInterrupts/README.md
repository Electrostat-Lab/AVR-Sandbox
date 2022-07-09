# HelloExternalInterrupts

<a name="CONTENTS"></a>
## Contents:
1) What's external interrupts ?
2) External Interrupt vector table.
3) Available external interrupts all over atmega328p as an example.
4) Operating external interrupts on atmega328p as an example.
--------------------
## 1) What's external interrupts ? [--Jump to contents--](#CONTENTS)

An external interrupt service routine is an event handler which is invoked whenever an external change to a specific pin takes place which sets the external interrupt flags (bits) to one enabling the interrupt routine handler.

The interrupt handler interrupts the program execution and jumps to the interrupt service subroutine, ie code inside the `ISR(VECTOR_NAME) {...}`.

For more refer to the official AVR lib C docs: [AVR-Interrupts AVR Lib C](https://software-hardware-codesign.github.io/AVR-Sandbox/docs/avr-libc/avr-libc-user-manual/group__avr__interrupts.html#ga68c330e94fe121eba993e5a5973c3162).

----------------
## 2) The External Interrupt vector table: [--Jump to contents--](#CONTENTS)

The interrupt service routine (ISR) vector is a reference to the memory address of the interrupt register that operates this type of interrupt service for the mcu.

The ISR vector can be referred by its name included for each chip in a vector table, for example: 

| `ISR Vector table for atmega328p` and `Vectors Mem Address` |
|----------------------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178115432-0224083b-a699-4526-8535-7e03a5fa1399.png) |

----------------
## 3) Available external interrupts all over atmega328p as an example: [--Jump to contents--](#CONTENTS)

In order to enable external interrupts, you have to set enable the enable bits inside the Mask and Control Status Registers.

Here are the mask/control status registers for the external interrupt handlers: 

| `EIMSK (External Interrupt Mask Register)` | `PCMSK0 (Pin Change Mask Register)` | 
|--------------------------------------------|-------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178116370-e5b00a09-adb3-451e-bfd7-cd84c7691f6a.png) | ![image](https://user-images.githubusercontent.com/60224159/178116431-1c4d13d7-6119-48fe-aeb6-990c9a3db457.png) |

| `PCMSK1 (Pin Change Mask Register)` | `PCMSK2 (Pin Change Mask Register)` | 
|---------------------------------------|-------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178116489-d92ed6dc-8ab0-486e-86e1-28968d86a5eb.png) | ![image](https://user-images.githubusercontent.com/60224159/178116503-ac2bd1ec-b834-4053-b631-db1364d13cbd.png) |

| `EICRA (External Interrupt Control Register) for controlling the interrupt pin state` | `PCICR (Pin Change Control Register) for enabling the pin change interrupt uints` |
|------------------------------------------------|------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178116574-7dfc3b0a-c1e1-44f6-80dc-a0dc39cb14fe.png) | ![image](https://user-images.githubusercontent.com/60224159/178116592-36acb4e1-31c2-4df5-870c-72769926438f.png) | 

| `PCIFR (Pin Change interrupt flag register), Handled by the interrupt service uint mainly` | 
|----------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178116734-eef0baa8-620c-4515-842b-9c7e40f66be7.png) |

----------------------------

## 4) Operating external interrupts on atmega328p as an example: [--Jump to contents--](#CONTENTS)

1) Enabling bit corresponding to the required interrupt service uint on the control status register (eg: BIT (PCIE0) on REG (PCICR)).

2) Enabling bit corresponding to the required PIN on the avr on the Mask Register (eg: BIT (PCINT0) on REG (PCMSK0)), use the main pin layout provided by the datasheet: 

| `Atmega328p MLF (Micro Lead Frame) SMD Package Pin Config` | `Atmega32A PDIP (Plastic-Dual-In-Package) Pin Config` | 
|--------------------------------------------------|-------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178118450-18ef663a-bd1a-4df8-9d38-425a4ed47ac4.png) | ![image](https://user-images.githubusercontent.com/60224159/178118473-f0783f82-bed1-4af0-bd7a-5b0ea5abad87.png) |

3) Setting the I-bit to one on the `SREG` by calling `sei();`.

```c
#include<avr/io.h>
#include<stdlib.h>
#include<avr/interrupt.h>
...
void GPIO::ExternalInterruptHandler::activatePCINT0(const uint8_t& INT_VEC) {
    PCICR |= (1 << PCIE0);
    PCMSK0 |= INT_VEC;

    sei();
}
```

4) Define the `ISR (Vector) {...}` block based on the vector table provided above.

5) Define a single obvserver method `GPIO::ExternalInterruptHandler::onPinChanged();` to complete the observer pattern, override this method in your application to listen for the external interrupt service.

```c
#include<avr/io.h>
#include<stdlib.h>
#include<avr/interrupt.h>
...
ISR (PCINT0_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (PCINT1_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (PCINT2_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}
```

6) ISR() code blocks are executed when the pin changes the state either from (HIGH) to (LOW) also known as (FALLING_EDGE) with a (LOGIC HIGH) value, or from (LOW) to (HIGH) aka (RISING_EDGE) with a (LOGIC_LOW) value, it depends on the initial state assigned from the software code which is either `HIGH_LEVEL` or `LOW_LEVEL`, a trigger change to the initial state can trigger the PCIF bits in PCIFR and jump the ISR() code.

| `An initial LOW state can be assigned from code` | `FALLING EDGE Trigger (from HIGH to LOW) -- LOGIC = HIGH` | `RISING EDGE Trigger (from LOW to HIGH) -- LOGIC = LOW` | 
|--------------------------------------------|-----------------------------------------|--------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178118774-72efe358-6089-4aae-987f-e9e210d19b9d.png) | ![image](https://user-images.githubusercontent.com/60224159/178118810-cf900223-aaa4-4169-9e66-7013de21168d.png) | ![image](https://user-images.githubusercontent.com/60224159/178118818-c94b10c7-0a1c-409b-bce6-bf71f2614dbf.png) | 

Code example: 
```c
/**
 * @brief Triggered when the PIN state is changing (From HIGH to LOW -- Falling edge -- LOGIC = 1) 
 *        and (From LOW to HIGH -- Rising edge -- LOGIC = 0). 
 */
void GPIO::ExternalInterruptHandler::onPinChanged() {
      /* print on the RISING edge (when PD4 is still LOW) -- FROM LOW TO HIGH Logic*/
      if (!isPCINT20Active()) {
          Serial::UART::getInstance()->sprintln((char*) "ON -- RISING EDGE");
          /* set the pin to HIGH LEVEL as of after the RISING EDGE */
          PORTD |= (1 << PD4);
      /* print on the FALLING edge (when PD4 is still HIGH) -- FROM HIGH TO LOW Logic*/
      } else if (isPCINT20Active()) {
          Serial::UART::getInstance()->sprintln((char*) "OFF -- FALLING EDGE");
          /* set the pin to LOW LEVEL as of after the FALLING EDGE */
          PORTD &= ~(1 << PD4);
      }
      reti(); /* exit to the main function */
}

int main(void) {
    Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600);
    /* Write PD4 to LOW */
    PORTD &= ~(1 << PD4);
    /* activate the external interrupt service routine handler on the PCINT20/PD4 */
    GPIO::ExternalInterruptHandler::getInstance()->activatePCINT2(1 << PCINT20);
    
    /* block as long as the pin is on the ZERO LEVEL */
    while (true) { 
        if (!isPCINT20Active()) {
            Serial::UART::getInstance()->sprintln((char*) "OFF -- LOW LEVEL");
        }
        _delay_ms(1000);
    } 

    while (1);
    return 0;
}
```

7) Connect this circuit example and test using the port reader bash script provided within `./HelloExternalInterrupts/build/`: 

![](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloExternalInterrupts/fritzing/External%20Interrupts%20Test%20Circuit.png)

8) Running the Serial port reader: 
```bash
pavl@pavl-machine:/home/twisted/GradleProjects/AVR-Sandbox/HelloExternalInterrupts/build$ sudo ./readPort.sh 
[sudo] password for pavl:             


Started reading PORT [/dev/ttyUSB0]

OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
ON -- RISING EDGE
OFF -- FALLING EDGE
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
OFF -- LOW LEVEL
```





