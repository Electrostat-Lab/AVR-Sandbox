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






