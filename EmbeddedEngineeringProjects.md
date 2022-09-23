## Requirements:

### Platforms to use:
- [x] Arduino UNO (mcu-atmega328p) - NANO - MEGA.
- [ ] Raspberry Pi.
- [ ] Beaglebone.

### RISC MCUs:
- [x] ATMEGA32A.
- [x] ATMEGA328p.

### USBasp Programmer

### Batteries:
- [x] 9v Batteries.
- [ ] 1.5v Batteries.

### Voltage regulators:
- [x] LM7805: a 5v regulator to power the atmega.
- [ ] LM7806: a 6v regulator for other uses.

### Breadboard.

### Resistors.

### Transistors:
- [x] TIP122.

### Jumper wires:
- [x] MALE to MALE.
- [x] MALE to FEMALE.

### Tools:
- [x] AVR-GCC.
- [x] Avrdude.
- [x] Arduino IDE.
- [ ] Java/JSerialComm/Serial4j (for advanced testing purposes).
- [ ] Geany on Raspbian OS.

--------------------------------------------------------------------------------

## Projects:
- R/W using Digital I/O (GPIO):
    1) Digital Traffic Lights Signals using delays and IO.
    2) TypeWriter calculator using push buttons.
    3) Piezo Christmas Songs using buzzers and push buttons. 
    4) Christmas LED strip with a pattern changing algorithms (switch pattern using push buttons).
    5) LED Matrix (4x4, 5x5, 6x6 ..etc, choose your own).
    6) Basic electric piano using push buttons and a buzzer.
    7) Basic music player using push buttons, a buzzer and LCD for switching songs (add 2 songs in code).
    <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand the digital IO signals.
    2) Perform boolean algebra on the IO signals.
    3) Use external interrupts as jump signals.
    4) Write standard embedded clean maintainable code.
    5) Learn how to use the voltage regulators, transistors, batteries and resistors together 
    in a single circuit with the MCU AtMega32A or AtMega328p.
    6) Learn how to debug using LCD and/or UART communications.
    ```
- ADC (Analog Digital Converter):


- UART (Universal Async R/T):
    1) UART controllable robot prototype (via Arduino IDE serial monitor).
    2) UART controllable LCD screen (displays what is typed in the serial monitor console).
    3) UART Ultrasonic obstacle detector sensor.
    


- PWM (Pulse Width Modulation):


- SPI (Serial Peripheral Interface):

- Timers:
  1) Kitchen microwave timer with a buzzer.
  2) Modify any of the above projects to use the timer interrupt service routine.

