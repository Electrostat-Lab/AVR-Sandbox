# HelloUART

Shows an example of using UART on atmega328p.

![image](https://user-images.githubusercontent.com/60224159/177357955-a0df1f00-4835-4968-86e7-d43e55c83155.png)


<a name="TOPICS"></a>

## Topics covered: 
1) Basics of UART protocol (the RS232 handshakes).
2) General layout of UART protocol on avr mcus.
3) Programming UART protocol on `atmega328p` using the polling method (blocks the main application execution signals until data acquisition starts).
4) Programming UART protocol on `atmega328p` using the UART interrupt service routine method (interrupts the main application execution signals when data acquisition finishes).

---------------------------------------
## 1) Basics of UART protocol and the RS232 Handshakes: [--Jump to topics--](#TOPICS)

- Data are transferred across UART in the form of 10-bit data frames, each frame is composed of 8-bit (1 byte) data with a start bit (aka space) and an end bit.

| `UART Data Frames` |
|----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177326358-c539073f-f1e7-4968-b9d3-5e1951ef5ae1.png) |

- Data transfer rate is recorded in bps (bit per second) which is referred to by the baud rate in the case of the modem environment.

| `The Baud Rate Calculation and the value of UBRR` | `The baud rate generation circuit` |
|-----------------|----------------|
| ![image](https://user-images.githubusercontent.com/60224159/177328623-399b6f68-eb1c-4568-a3e3-e12fa2e95579.png) | ![image](https://user-images.githubusercontent.com/60224159/177329318-cd7196d4-9a61-4b4c-956c-46dcffbfa056.png) |


Pre-requisite for transfering data between 2 devices (the handshaking strategy pattern) : 
- 2 Devices, a modem (aka DCE for Data communication equipment) and a PC terminal (aka DTE for Data terminal equipment).
- `DTR for Data Terminal Ready` signal: triggered by the DTE when the terminal and the COM port is ready.
- `DSR for Data Set ready` signal: triggered by the modem (DCE) when the modem is on and ready.
- `RTS for Request to send` signal: triggered by the DTE device (PC) when there is a byte to transmit to the modem.
- `CTS for Clear to send` signal: triggered by the DCE (the modem) in response to the `RTS` signal when there is enough room to receive data on the modem, otherwise the DCE will not assert the CTS signal and the DTE (Data terminal equipment) will re-assert the DTR signal and RTS signal again.
- `DCD for Data carrier detect` signal: triggered by the DCE (modem) when a valid data carrier is available to carry the byte transfer.
- `RI for Ring indicator` signal: triggered by the DCE (modem) when an incoming call is executed.
- `Tx/Rx for data receive and transmit` signals: SG system (Signal~Ground System).
- `GND for Ground`.

Note: 
Theses handshaking signals are for old systems using RS232 DB9 by IBM and not supported by the AVR.

| `RS232 Port and Handshake signals` |
|-----------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177342916-db2c02d7-0388-4607-bf82-f57d63d15d98.png) | 

---------------
## 2) General layout of AVR UART Registers: [--Jump to topics--](#TOPICS)
To activate the UART protocol on the avr, we have to deal with a couple of registers: 
- UCSRA (USART Control Status Register): Listens for different actions on the avr including data transmit and receive.
- UCSRB (USART Control Status Register): Controls the operation of the avr including enabling Tx/Rx and interrupt service subroutine.
- UCSRC (USART Control Status Register): Controls the data frame size.
- UBRR (USART Baud Rate Register): Sets the baud rate (bps).
- UDR (USART Data Register): Holds the 8-bit data of the UART, the 9th bit mode can be activated by setting the `UCSZ0/UCSZ1/UCSZ2` from `UCSRC` to 1 and read the 9th bit from the `RXB8/TXB8` from `UCSRB`.

Here are the illustrative tables from the datasheet: 
| `UBBR values for different baud rates within a CLK Fosc` | `UCSRA Register bits` |
|-----------------------|-------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177358158-730eb25a-0115-4e28-adfc-33a675c1b343.png) | ![image](https://user-images.githubusercontent.com/60224159/177361060-6411300e-d7cc-4101-a4a8-69ac8b13fe45.png) |

 | `UCSRB Register bits` | `USCRC Register bits` |
 |----------------------|-----------------------|
 | ![image](https://user-images.githubusercontent.com/60224159/177361355-07f5abc3-1fcb-4b21-8a71-d5629143f47c.png) | ![image](https://user-images.githubusercontent.com/60224159/177361571-72cce3fc-744b-4a6e-a96d-6cbe62d08dc5.png) |

| `Data frame modes` |
|--------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177403721-8123dabe-1555-4e1e-a5b7-29c7dfa64c4c.png) |

----------------------
## 3) Programming UART protocol on `atmega328p` using the polling method: [--Jump to topics--](#TOPICS)
The Polling method blocks the main execution signals until data acquisition takes place:
- Enabling the transmitter and the receiver bits `TXEN/RXEN` of `UCSRB`.
- Enabling the `UCSZ0` and `UCSZ1` of `UCSRC` register for 8-bit frame transmission.
- Enabling the 2-stop bits by setting the `USBS` of the `UCSRB`.

```c
void Serial::UART::startProtocol(const uint8_t& BAUD_RATE_VAL) {
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // TXEN_BIT = 1, enables the transmitter buffer register.
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // enables the UCSZ0, UCSZ1 and URSEL
    UBRR0 = BAUD_RATE_VAL; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}
```
- When writing a character to the Tx: 
1) Get the byte for the `UDRE` (USART Data Register Empty) by using `1 << UDRE0` which is the same as this byte (0b00100000).
2) Listen for the activation of the UDRE bit on the UCSRA **only** by using `while (UCSRA & (1 << UDRE0) != (1 << UDRE0));`, the activation of UDRE0 bit will un-trigger the loop and continue the code execution at the main signal.
3) A simplification for the above code is `while (!(UCSRA & (1 << UDRE0)));` in which the code execution is blocked whenever the bit UDRE0 is zero by flipping the boolean result to true, and when the UDRE0 is set (which means we are ready to transmit new data) the result is also flipped to false and the while () is ignored.

```c
void Serial::UART::cprint(char& data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}
```
- When reading a charachter from the Rx: 
1) Get the byte for the `RXC`  (Receive complete register) by using `1 << RXC0` which is the same as (0b10000000).
2) Listen for the activation of the RXC bit on the USCRA **only** by using `while (UCSRA & (1 << RXC0) != (1 << RXC0));`, this will block the main line of execution until the bit RXC0 is triggered once the charachter frame (8-bit + 2-bit) is completed.
3) A simplification for the above code is `while (!(UCSRA & (1 << RXC0));` which the negate the boolean to true when RXC0 is zero, triggering the waiting loop and negate the boolean value to false when RXC0 is 1, dismissing the waiting loop.

```c
uint8_t Serial::UART::readASCII() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
```
---------------------------------
## 4) Programming UART protocol on `atmega328p` using the UART interrupt service routine method: [--Jump to topics--](#TOPICS)
It interrupts the main application execution signals when data acquisition finishes:
- Enabling the Receive complete interrupt `RXCIE` and Transmit interrupt services `TXCIE` and the data register interrupt `UDRIE`.
- Use the ISR (interrupt service routine) `ISR(USART_RXC_vect)` for the RX complete and `ISR(USART_UDRE_vect)` for the data register empty interrupt service event.
- Trigger `sei();` to start the interrupt service unit.
- For data transmit from the avr: 
```c
#include<avr/io.h>
#include<string.h>
#include<stdlib.h>
#include<avr/interrupt.h>
...

/**
 * @brief Triggered when the bit UDRE0 is one (the data register buffer is empty).
 */
ISR (USART_UDRE_vect) {
    UDR0 = *(Serial::UART::getInstance()->transmitData);
    Serial::UART::getInstance()->stopDataRegisterEmptyBufferISR();
}

/**
 * @brief Triggered when the bit TXC is settled and the data transmission has been completed.
 */
ISR (USART_TX_vect) {
    Serial::UART::getInstance()->onDataTransmitCompleted((const uint8_t) UDR0);
    Serial::UART::getInstance()->stopTransmitterISR();
}

void Serial::UART::startTransmitterISR() {
    UCSR0B |= (1 << TXCIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopTransmitterISR() {
    // Finds the 1s complement of all bits in TXCIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << TXCIE0); 
}

void Serial::UART::startDataRegisterEmptyBufferISR() {
    UCSR0B |= (1 << UDRIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopDataRegisterEmptyBufferISR() {
    // Finds the 1s complement of all bits in UDRIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << UDRIE0); 
}
```
- For data receive from the avr: 
```c
#include<avr/io.h>
#include<string.h>
#include<stdlib.h>
#include<avr/interrupt.h>
...

/**
 * @brief Triggered when the RXC0 is settled and the receiving has been completed.
 */
ISR (USART_RX_vect) {
    Serial::UART::getInstance()->onDataReceiveCompleted(Serial::UART::getInstance()->readASCII());
}

void Serial::UART::startReceiverISR() {
    UCSR0B |= (1 << RXCIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopReceiverISR() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << RXCIE0); 
}
```
See [HelloUART.c](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloUART/main/lib/HelloUART.c) for more about the USART protocol implementation in atmega328p.
