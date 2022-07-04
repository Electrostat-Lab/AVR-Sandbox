## HelloAnalogRead

Shows an example of using ADC pins to read data from a potentiometer connected to ADC0.

### The UART protocol Layout: 

Refer to [HelloUART tutorial](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/tree/master/HelloUART) for more.

--------------
### The ADC Protocol Layout: 

![image](https://user-images.githubusercontent.com/60224159/177138088-32a4244c-2c3f-4c8d-8ddd-51e896dccf6a.png)

#### 1) Some of the major characteristics of the ADC:
- Resolution
- Conversion time
- Vref
- Digital Data output
- Parallel vs Serial ADC
- Analog input channels
- Start conversion and end of conversion (EOC) signals
- Successive approximation ADC

#### 2) Operating ADC in `atmega328p` using C avr lib:
To operate the ADC in the atmega32, you will need to study the `ADMUX` of the multiplexer which encodes the ADC pins and the status and control 
register `ADCSRA` of the avr:

<a name="ADMUX"></a>

- ADMUX: ADC multiplexer selection register:

| `ADMUX Register Bits` |
|-----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177139833-081cbe02-556b-4bf5-a9af-4ccb066e37b6.png) |

| `AREF Truth table` | `The ADLAR Bit` | `MUX Bits` | 
|------------------------|-------------------|-------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177140256-67d3e506-b64d-4244-9741-0dec0dfd6974.png) | ![image](https://user-images.githubusercontent.com/60224159/177141673-738104e3-580b-45b1-aacc-636efaa1a7c8.png) | ![image](https://user-images.githubusercontent.com/60224159/177140612-feb0c8c3-c81a-4e3f-9a18-75c70d99a5fa.png) |


- ADSCRA: ADC Control and Status Register:

| `ADCSRA Register Bits` | 
|------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177142491-bb6aa25e-7377-4627-ba30-95f7483561d0.png) |

<a name="COVERSION"></a>

| `ADC Start Conversion bit` |
|----------------------------|
| To start the ADC Conversion, setting the bit `ADSC` of the `ADCSRA` register to true is an essential step, furhter more the `ADIE` enables the interrupt service routine for the ADC conversion onComplete and the `ADIF` is set to true when the conversion is completed |

| `A/D Conversion time` |
|-----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177149300-3611afc3-43a1-4a77-976b-d8c8b6cb36ee.png) |

- ADCL: ADC Low Byte Register
- ADCH: ADC High Byte Register

| For more about the internals of the ADC, here is a good article showing the operation of an ADC (MCP3008) with the raspberry pi in depth |
|-------------------------------------------------|
| https://pi4j.com/featured-projects/joystick-game/ |

--------------

### Steps of implementing the ADC protocol using AVR lib c:

1) Adjusting the `ADMUX` register: to enable the ADC protocol, the interrupt service handler and the clock pre-scaler to valid clock greater than 200k HZ from the Fosc value (frequency of the crystal oscillator): [--Jump to ADMUX Docs--](#ADMUX)
```c
void Analog::Adc::startProtocol() {
    /* setup ADCSRA */
    ADCSRA = (1 << ADEN) /*enable adc protocol*/ | (1 << ADIE) /*enable interrupt service*/ 
                | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) /*set clock prescaler to clk/128*/; 
}
```
2) Start the conversion on an ADC_MUX code which encodes for `ADC0...ADC7` according to a truth table: [--Jump to A/D Conversion Docs--](#COVERSION)
```c
/* define analog ADC pins based on the multiplexers codes */
#define ADC_MUX0 ((const uint8_t) 0x00)
#define ADC_MUX1 (ADC_MUX0 + 0x01)
#define ADC_MUX2 (ADC_MUX1 + 0x01)
#define ADC_MUX3 (ADC_MUX2 + 0x01)
#define ADC_MUX4 (ADC_MUX3 + 0x01)
#define ADC_MUX5 (ADC_MUX4 + 0x01)
#define ADC_MUX6 (ADC_MUX5 + 0x01)
#define ADC_MUX7 (ADC_MUX6 + 0x01)
...
void Analog::Adc::startConversion(const uint8_t& PIN) {
    /* setup ADMUX */
    ADMUX = 0b01000000 | PIN; /* 1 for REFS0 for (VREF = VCC) */
    ADCSRA |= (1 << ADSC); /* the last step: start conversion */
}
```
3) Read the analog data using `uint16_t Analog::Adc#analogRead()` inside the interrupt service subroutine `ISR(ADC_vect) {...}` and then re-start conversion to trigger the interrupt service handler again for continous monitoring: 
```c
uint16_t Analog::Adc::analogRead() { 
    volatile uint8_t adcl = ADCL; /* ADCL must be read before ADCH */
    volatile uint8_t adch = ADCH;
    return ((0x00 | adch) << 8) | adcl; /* concatenate the 2 (8-bit registers) in a 16-bit software register */
}
```
4) The code example [HelloAnalogRead.c](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloAnalogRead/main/lib/HelloAnalogRead.c).

-------------

### Uploading code and reading from the serial port: 
1) Install the avr dude through [Avr-dude-install](https://github.com/avrdudes/avrdude#documentation).
2) Connect the programmer to the laptop.
3) Adjust the variables (the chip board, baud rate and the programmer) accordingly, for more refer to avr-dude-docs:
- [Avr-dude-table-of-contents](https://avrdudes.github.io/avrdude/7.0/avrdude_toc.html#SEC_Contents).
- [Avr-dude-docs](https://avrdudes.github.io/avrdude/7.0/avrdude.html).
- [Avr-dude-options-docs](https://avrdudes.github.io/avrdude/7.0/avrdude_3.html#Option-Descriptions).
- [Avr-dude-Command-line-examples](https://avrdudes.github.io/avrdude/7.0/avrdude_5.html#Example-Command-Line-Invocations).
```bash
#**
#* Ccoffee Build tool, manual build, alpha-v1.
#*
#* @author pavl_g.
#*#

# define work directory
# 1) print the current working directory to a string value
pwd=`pwd`
# cut the working directory from its end by a one '/' delimiter
project="${pwd%/*}"
# cut the working directory from its end by a one '/' delimiter again
rootProject="${project%/*}"
# pass the value of the dire

clibName=('libHelloAnalogRead')
# AVR-DUDE properties
BAUD_RATE='57600'
PORT='/dev/ttyUSB0'
CHIP='atmega328p'
CHIP_ALIAS='m328p'
PROGRAMMER='arduino'
# Common Variables contain colors
source ${rootProject}'/CommonVariables.sh'
source ${rootProject}'/AVR__HOME.sh'
output=${project}'/output/'${clibName}
```
4) Navigate to the `AVR-Sandbox/HelloAnalogRead/build/` and run: 
```bash
cd ../AVR-Sandbox/HelloAnalogRead/build/
./build
```
5) To compile only use `./compile`.
6) To read from the serial port, run `sudo ./readPort`.
```bash
pavl@pavl-machine:/home/twisted/GradleProjects/AVR-Sandbox/HelloAnalogRead/build$ sudo ./readPort.sh 
[sudo] password for pavl:             


Started reading PORT [/dev/ttyUSB0]

510
510
510
510
511
509
1022
1021
1023
1022
510
982
1023
510
510
221
0
184
0
0
506
3
0
510
1023
510
```
