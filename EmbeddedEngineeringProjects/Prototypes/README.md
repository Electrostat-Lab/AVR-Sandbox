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
    8) UART Ultrasonic obstacle detector sensor.
    9) Ultrasonic eye using an LED screen.
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
    1) Voltage reader device monitor using LCD (or UART) and ADC.
    <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand the initialization of ADC.
    2) Understand the basic 8-bit read.
    3) Understand how to read a 10-bit data.
    4) Understand the Vref and how to set it up.
    ```

- UART (Universal Async R/T):
    1) UART controllable robot prototype (via Arduino IDE serial monitor).
    2) UART controllable LCD screen (displays what is typed in the serial monitor console).
    
    <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand how the UART works.
    2) Interface IO with UART using RS232 port interface (usb now).
    3) Control MCU behavior over UART signals.
    4) Perform synchronous and async operations using UART.
    5) Understand how the ultrasonic works and interface it with the mcu.
    ```    

- PWM (Pulse Width Modulation):
    1) Small standing robot controllable over buttons or UART (up to you).
    2) Obstacle avoider robot prototype using Ultrasonic.
    <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand how to make pwm signals.
    2) Understand how motors work.
    3) Understand basic robotics.
    ``` 
    
- SPI (Serial Peripheral Interface):
    1) Interface with the 10-bit MCP3008 ADC and send data over UART to the arduino serial monitor.
    2) Temperature controllable CPU fan (PWM + SPI).
    <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand how to use the SPI driver.
    2) Understand how MCP3008 ADC works.
    3) Understand how to read data sheets and interpret it to code properly.
    ``` 

- Timers:
     1) Kitchen microwave timer with a buzzer.
     2) Modify any of the above projects to use the timer interrupt service routine.

     <br>
    
    ```
    After these tasks, the learner should be able to:
    1) Understand how timers work.
    2) Understand how to initialize timers and set its deadline.
    3) Understand timer interrupts.

    ```
