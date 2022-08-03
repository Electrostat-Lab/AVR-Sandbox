# Hello-SPI

<a name="TOPICS"></a>
## Topics Covered: 
1) SPI basics.
2) SPI Register in atmega32A/atmega328p.
3) SPI Implementation for atmega32A/atmega328p.
4) Operating MCP3008 ADC using SPI.
---------------------------------------------------------------------------

## 1) SPI basics: [--Jump to Topics--](#TOPICS)

The SPI (serial peripheral interface) is a bus interface connection incorpo-
rated into many devices such as ADC, DAC, and EEPROM.

In this tutorial, we are going to show off the basics of the SPI protocol and interfacing with MicroChip MCP3008 10-bit ADC as an example.

- SPI data line scheme: 

![image](https://user-images.githubusercontent.com/60224159/182619253-96d607d6-45e7-4d42-a66a-6410280b9ed6.png)

- In SPI communication, the master and slave(s) must agree on the clock polarity and phase with respect to the data. 
- Freescale names these two options as CPOL (clock polarity) and CPHA (clock phase) and they define the SPI protocol mode of operation.
- Adjusting Clock Polartiy and Phase to determine the SPI Mode: 

| `Clock Polarity (CPOL)` | `Clock Phase (CPHA)` | 
|-------------------------|----------------------|
| Determines the base value of the Serial Clock, either HIGH or LOW | Determines when to sample data, either on the leading edge or on the trailing edge |

- Available SPI modes: 

| `SPI Mode 0 (MODE_0_0)` | `SPI Mode 1 (MODE_0_1)` | `SPI Mode 2 (MODE_1_0)` | `SPI Mode 3 (MODE_1_1)` |
|-------------------------|-------------------------|-------------------------|-------------------------|
| CPOL = 0, base value of SCLK is LOW | CPOL = 0 | CPOL = 1, base value of SCLK is HIGH | CPOL = 1 | 
| CPHA = 0, sample data on the leading edge of the SCLK, aka on the rising edge | CPHA = 1, sample data on the trailing edge of the SCLK, aka on the falling edge | CPHA = 0, sample data on the leading edge, aka falling edge | CPHA = 1, sample data on the trailing edge, aka the rising edge |

- SPI data transmission scheme in different modes: 

![image](https://user-images.githubusercontent.com/60224159/182621166-897f775b-3ef8-4310-ab72-64445288e782.png)

---------------------------------------------------------------------------------------

## 2) SPI Registers in atmega32A/atmega328p: [--Jump to Topics--](#TOPICS)

- The SPI Control Register (SPCR): Controls the SPI including operating, SPI Clock speed, SPI Clock modes, and transmission type either MASTER or SLAVE.
- The SPI Status Register (SPSR): Monitors the SPI flags and controls the SPI clock speed.
- The SPI Data Register (SPDR): Sends and receives data to and from the SPI Master device using the SCLK.

| `SPCR` | `SPSR` | `SPDR` | 
|--------|--------|--------|
| ![image](https://user-images.githubusercontent.com/60224159/182670438-143b0e13-2a80-443e-abfb-7d213ab39963.png) | ![image](https://user-images.githubusercontent.com/60224159/182670344-78c64a5a-6f81-4fba-835a-fadacba3f9aa.png) | ![image](https://user-images.githubusercontent.com/60224159/182670591-497d28fe-32ee-41a5-8cc9-02af76c0109a.png) | 

| `SPI Clock Speed Configurations` |
|----------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/182670775-4569c210-9641-45d3-a092-cd3ca2d71041.png) |

-----------------------------------------------------------------------------------------

## 3) SPI Implementation for atmega32A/atmega328p: [--Jump to Topics--](#TOPICS)

1) Setup pins directions using DDRX (data direction registers) for MOSI, SCLK, SS and MISO according to data transmission and the user manual: 

```c
/** Define SPI pins according to the device and the datasheet */
#if defined (__AVR_ATmega32__)
#   define MISO 6
#   define MOSI 5
#   define SCK 7
#elif defined (__AVR_ATmega328P__)
#   define MISO 4
#   define MOSI 3
#   define SCK 5
#endif 
```
```c
if (transmissionType == MASTER) {
    /* define user-defined pins as output */
    DDRB |= (1 << MOSI) | (1 << SCK);
} else if (transmissionType == SLAVE) {
    DDRB |= (1 << MISO);
}
```
```c
/* set slave select as output */
DDRB |= (1 << SS_PIN);
```
The SS_PIN is trivial and you can choose to add as many SS as you want, the SS initializes the SLAVE communication and ends the communication with the MASTER.

2) Setup SPI clock speed with respective to the Fosc: 

```c
/** Defines the SPI rate with respect to the Fosc */
#define Fosc_1_4  ((SPIFosc) 0.25)
#define Fosc_1_16 ((SPIFosc) 1/16)
#define Fosc_1_64 ((SPIFosc) 1/64)
#define Fosc_1_128 ((SPIFosc) 1/128)
#define Fosc_1_2 ((SPIFosc) 0.5)
#define Fosc_1_32 ((SPIFosc) 1/32)
...

if (spiFosc == Fosc_1_2) {
    /* flip SPR0/1 to zero */
    SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
    /* flip SPI2X bit to one */
    SPSR |= (1 << SPI2X);
} else if (spiFosc == Fosc_1_4) {
    /* flip SPR0/1 to zero */
    SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
    /* flip SPI2X bit to zero */
    SPSR &= ~(1 << SPI2X);
} else if (spiFosc == Fosc_1_16) {
    /* flip SPR0 to one and SPR1 to zero */
    SPCR = (SPCR & ~(1 << SPR1)) | (1 << SPR0);
    /* flip SPI2X bit to zero */
    SPSR &= ~(1 << SPI2X);
} else if (spiFosc == Fosc_1_32) {
    /* flip SPR0 to zero and SPR1 to one */
    SPCR = (SPCR & ~(1 << SPR0)) | (1 << SPR1);
    /* flip SPI2X bit to one */
    SPSR |= (1 << SPI2X);
} else if (spiFosc == Fosc_1_64) {
    /* flip SPR0/1 to one */
    SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
    /* flip SPI2X bit to one */
    SPSR |= (1 << SPI2X);
} else if (spiFosc == Fosc_1_128) {
    /* flip SPR0/1 to one */
    SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
    /* flip SPI2X bit to zero */
    SPSR &= ~(1 << SPI2X);
}
```
3) Setup SPI Clock MODE either Mode_0, Mode_1, Mode_2 or Mode_3: 

```c
/** Serial Data modes sampling */
#define MODE_0_0 (ModeOfTransmission (SPCR & (~(1 << CPOL) & ~(1 << CPHA))))
#define MODE_0_1 (ModeOfTransmission (SPCR & (~(1 << CPOL) | (1 << CPHA))))
#define MODE_1_0 (ModeOfTransmission (SPCR & ((1 << CPOL) & ~(1 << CPHA))))
#define MODE_1_1 (ModeOfTransmission (SPCR & ((1 << CPOL) | ((1 << CPHA))))
```
4) Setup the transmission type, either MASTER or SLAVE: 

```c
/** Defines the [TransmissionType] datatype */
#define TransmissionType int

/** Defines the [MASTER] and [SLAVE] transmission modes */
#define MASTER (TransmissionType (1 << MSTR))
#define SLAVE (TransmissionType (SPCR & ~(1 << MSTR)))
```
5) Now add the SPCR command to start the protocol with some configuration: 

```c
...
/* start the protocol */
SPCR |= (1 << SPE) | (transmissionType) | MODE;
```
The final function to start the SPI protocol would look like: 
```c
void Serial::SPI::startProtocol(const TransmissionType& transmissionType, const SPIFosc& spiFosc, const ModeOfTransmission& MODE) {

    if (transmissionType == MASTER) {
        /* define user-defined pins as output */
        DDRB |= (1 << MOSI) | (1 << SCK);
    } else if (transmissionType == SLAVE) {
        DDRB |= (1 << MISO);
    }

    SPCR = 0x00;

    if (spiFosc == Fosc_1_2) {
        /* flip SPR0/1 to zero */
        SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_4) {
        /* flip SPR0/1 to zero */
        SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    } else if (spiFosc == Fosc_1_16) {
        /* flip SPR0 to one and SPR1 to zero */
        SPCR = (SPCR & ~(1 << SPR1)) | (1 << SPR0);
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    } else if (spiFosc == Fosc_1_32) {
        /* flip SPR0 to zero and SPR1 to one */
        SPCR = (SPCR & ~(1 << SPR0)) | (1 << SPR1);
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_64) {
        /* flip SPR0/1 to one */
        SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_128) {
        /* flip SPR0/1 to one */
        SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    }
    /* start the protocol */
    SPCR |= (1 << SPE) | (transmissionType) | MODE;
}
```
6) Generating clocks with specific width (or delay): 
```c
void Serial::SPI::generateSCLK(const uint32_t& count, const uint8_t& width) {
    for (uint32_t i = 0; i < count; i++) {
        PORTB &= ~(1 << SCK);
        _delay_us(width / 1000);
        PORTB |= (1 << SCK);
        _delay_us(width / 1000);
    }
}
```
7) Writing data to the SPDR: 
```c
/** Defines boolean flags */
#define isTransmissionCompleted() ((boolean) (SPSR & (1 << SPIF)))
...
void Serial::SPI::write(const uint8_t& data) {
    SPDR = data;
    while (!isTransmissionCompleted());
}
```
----------------------------------------------------------------

## 4) Operating MCP3008 ADC using the SPI data bus interface: [--Jump to Topics--](#TOPICS) 

- `MCP3008`: is a write-only 10-bit Analog-to-Digital converter powered by a voltage comparator and a multiplexer, it operates using the SPI data bus interface.
- To operate MCP3008 as a SLAVE, the MASTER and the SLAVE should agree on an SPI Clock Mode specified in the SLAVE's device datasheet, in this case, its modes [MODE_0_0] and [MODE_1_1].

| `General Charachteristics` | `Packages overview` | 
|----------------------------|---------------------|
| ![image](https://user-images.githubusercontent.com/60224159/182679789-1b577786-407f-4cab-9f14-8ab39a742356.png) | ![image](https://user-images.githubusercontent.com/60224159/182684477-b7b5bbdf-8a31-4a98-86c0-17b21015e62e.png) |
| Dark Red: refers to the resolution and the channels for each package | Dark red: the AIN Channels and the Vref for resolution channel (comparator resolution) |
| Light Red: refers to the supported SPI modes of operation | Green: Vin |
| Green: refers to a brief electrical charachteristics including operating voltage and maximum current draw (in case of low resistivity status circuit) | Black: GNDs |
| Orange: refers to the packages available in the market | Blue: the SPI lines |

- Protect the device functionality by not exceeding these red flags:

| `Absolute charachteristics` | 
|-------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/182681765-62eaf885-1117-47c9-8497-b8e7b7c88437.png) |

- The SPI Clock charachteristics: 

| `Clock Data` | `General SPI Clock diagram of the operation` |
|--------------|----------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/182683644-aef17765-b967-4b67-a54b-7343ab460300.png) | ![image](https://user-images.githubusercontent.com/60224159/182685543-c6d2900f-24bf-458d-a63f-be790fb3d3d7.png) |

- The data frames on DIN and DOUT: 

| `Serial Data frames` |
|----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/182687365-3bd6d3b8-8b48-4ca3-ba42-09e6718379b8.png) |
| Blue: the SPI data lines |
| Purple: the CS or SS delay timings |
| Green Square: represents the starter byte written to the SPDR of the atmega32 at the DIN (MOSI or COPI) before the 1st 8-clocks | 
| Blue Square: represents the CHANNEL configuration byte written to the SPDR of the atmega32 at the DIN (MOSI or COPI) before the 2nd 8-clocks | 
| Red Square: represents the data read from the SPDR at the DOUT (MISO or CIPO) line after the last 8-clocks |


- MCP3008 Modes SPI operation, the MCP3008 can operate only in 2 SPI modes (MODE0 and MODE1):

| `SPI Mode_0` | `SPI Mode_3` |
|--------------|--------------|
|![image](https://user-images.githubusercontent.com/60224159/182698382-08efa788-0059-4dcb-9de5-89855a58021a.png) | ![image](https://user-images.githubusercontent.com/60224159/182695490-94d76ef8-4d18-4d67-81f1-9b17de40b19a.png) |
| In this mode the SPI CLK starts with LOW specified by [CPOL = 0] and the data is sampled at the leading edge specified by [CPHA = 0] | In this mode the SPI CLK defaults to HIGH specified by [CPOL = 1] and the data is sampled at the trailing edge specified by [CPHA = 1] |
| Green dot and square: refers to the starter byte loaded to the SPDR before the first 8 clocks | 
| Blue dot and square: refers to the configuration byte loaded to the SPDR before the second 8 clocks | 
| Red dot and square: refers to the data read from the SPDR after the transmission of the last two 8 clocks | 
| Orange: refers to the data write to the SPDR sampling state, the falling edge of the clk | 
| Purpule/Pink: refers to the data read from SPDR sampling state, the rising edge of the clk |

