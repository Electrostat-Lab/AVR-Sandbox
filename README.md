# <img src="https://user-images.githubusercontent.com/60224159/178119492-91d3cc70-a88f-4b9a-94a0-ca7b68b1d861.png" width="130" height="85"> AVR-Sandbox 

This repository lists down some useful testcases and common logical algorithms using `AVR-CORE` that are widely used in the field of hardware development and embedded systems, 
we will work on `arduino-nano` which is based on `atmega328p` also plain atmega is supported.

The testcases directrly access the `atmega328p`'s registers ports and their individual pins.

## Block Diagram for AVR Architecture parts: 

![image](https://user-images.githubusercontent.com/60224159/178119440-5a0fb95e-3dc6-4bc5-af58-9992d5c60221.png)

## Atmega328p packages pin config :

| `Atmega328p Pin Config` |
|---------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178119359-772c1963-6be5-4773-8e59-d9e5f5dcf3ba.png) |

| `Arduino Nano Pin Config` | 
|-------------------------|
| ![](https://software-hardware-codesign.github.io/AVR-Sandbox/Pinout-NANO_latest.png) |

## Documentations:
- [AVR-C-Lib Docs](https://software-hardware-codesign.github.io/AVR-Sandbox/docs/avr-libc/avr-libc-user-manual/index.html)
- [Lib-Iberty Docs](https://software-hardware-codesign.github.io/AVR-Sandbox/docs/libiberty/libiberty.html)
- [Operating On Windows Terminal](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloWindowsTerminal/README.md)
- [Serial4j API Docs](WIP)
- [Code of conduct and orientation around using AVR-Sandbox](WIP)

## Datasheets:

## Current Projects and Tech demos: 
- [Avr-lib C code basics Docs](https://software-hardware-codesign.github.io/AVR-Sandbox/AvrDataTypes) - [Example](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/AvrDataTypes/main/lib/AvrDataTypes.c)
- [USART Protocol](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloUART) - [Example](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloUART/main/lib/HelloUART.c)
- [ADC Protocol](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloAnalogRead) - [Example](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloAnalogRead/main/lib/HelloAnalogRead.c)
- [External Interrupts](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloExternalInterrupts) - [Example](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloExternalInterrupts/main/lib/HelloExternalInterrupts.c)
- [Timer Interrupts](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloTimerInterrupts) - [Example](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloTimerInterrupts/main/lib/HelloTimerInterrupt.c)
- [Running AtMega32A on a 9v/300mAmps battery](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloUsbAsp)
- [MPLAB.X IDE Example](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloMPLab.X)
- [Examples and tech demos](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/projects/1?fullscreen=true)
