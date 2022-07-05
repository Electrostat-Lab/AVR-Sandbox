# HelloUART

Shows an example of using UART on atmega328p.

![image](https://user-images.githubusercontent.com/60224159/177357955-a0df1f00-4835-4968-86e7-d43e55c83155.png)


<a name="TOPICS"></a>

## Topics covered: 
1) Basics of UART protocol (the RS232 handshakes).
2) General layout of UART protocol on avr mcus.
3) Programming UART protocol on `atmega328p`.

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
## 2) General layout of AVR UART Registers: 
To activate the UART protocol on the avr, we have to deal with a couple of registers: 
- UCSRA (USART Control Status Register) 
- UCSRB (USART Control Status Register) 
- UCSRC (USART Control Status Register) 
- UBRR (USART Baud Rate Register)
- UDR (USART Data Register)

Here are the illustrative tables from the datasheet: 
| `UBBR values for different baud rates within a CLK Fosc` | `UCSRA Register bits` |
|-----------------------|-------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177358158-730eb25a-0115-4e28-adfc-33a675c1b343.png) | ![image](https://user-images.githubusercontent.com/60224159/177361060-6411300e-d7cc-4101-a4a8-69ac8b13fe45.png) |

 | `UCSRB Register bits` | `USCRC Register bits` |
 |----------------------|-----------------------|
 | ![image](https://user-images.githubusercontent.com/60224159/177361355-07f5abc3-1fcb-4b21-8a71-d5629143f47c.png) | ![image](https://user-images.githubusercontent.com/60224159/177361571-72cce3fc-744b-4a6e-a96d-6cbe62d08dc5.png) |



