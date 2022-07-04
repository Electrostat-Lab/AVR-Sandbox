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








