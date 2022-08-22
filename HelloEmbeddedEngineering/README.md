# Contents: 
- Volatge, Current and basic components (circuits, resistors, transistors, batteries).
- Embedded engineering principles questions (boolean algebra and digital electronics).
- Embedded basic C/C++ (data types, variables, pointers, buffers and functions)
- GNU C Compiler (GCC) and Scripting languages questions.
- Advanced embedded engineering questions.
- Advanced C/C++.
- Design patterns and algorithms.

---------------------------------------------------------

## Volatge, Current and basic components:

1) Resistors are used for which of the following: 
    - [ ] Current limiting devices according to Ohm's law.
    - [ ] Current limiting devices according to KCL.
    - [ ] Voltage divider devices according to KVL.
    - [ ] Current dividers accoridng to KCL.
    - [x] A, C & D.

2) The following circuit shows the usage of resistors as -----------

    ![image](https://user-images.githubusercontent.com/60224159/185787594-5e076199-95c6-4a31-86c5-93239606db30.png)

    - [x] Voltage dividers.
    - [ ] Current dividers.
    - [ ] Current limiters.
    - [ ] A and C.

3) The following circuit shows the operation of resistors as -----------

    ![image](https://user-images.githubusercontent.com/60224159/185788864-d9df48d9-a705-464d-8474-10d0a3d011cf.png)

    - [ ] Current limiting devices according to Kirchhoff's current law (KCL).
    - [ ] Voltage limiting devices.
    - [x] Current limiting devices according to ohm's law.
    - [ ] A and C.

4) In the following circuit, V(P) can be solved using -------------

    ![image](https://user-images.githubusercontent.com/60224159/185789652-6c829abc-9fe4-4a37-a094-594b5c4d0426.png)

    `HINT: (I) isn't known here, so you should choose the equation that substitutes it.`

    - [x] Kirchhoff's Current Law (KCL).
    - [ ] Ohm's law.
    - [ ] KVL.
    - [ ] A and C.

5) In the following circuit, the resistance of R(s) can be solved using -------------

    ![image](https://user-images.githubusercontent.com/60224159/185788864-d9df48d9-a705-464d-8474-10d0a3d011cf.png)

    - [x] Kirchhoff's Voltage Law (KVL).
    - [ ] Ohm's law.
    - [ ] Thevinin's effect.
    - [ ] A and B.

6) Batteries connected in series are used for --------------
    - [x] increasing the voltage (KVL).
    - [ ] increasing the current (KCL).
    - [ ] increasing the resistance.
    - [ ] A and B.

7) Batteries connected in parallel are used for --------------
    - [x] increasing the current (KCL).
    - [ ] increasing the voltage.
    - [ ] increasing the power dissipation.
    - [ ] A and B.

8) The following circuit shows the operation of batteries in series ? 

    ![image](https://user-images.githubusercontent.com/60224159/185791637-082f7aae-cafc-4b81-813d-3d0c3265225d.png)

    - [x] true.
    - [ ] false.

9) The following circuit aims at increasing the circuit voltage and current ?

    ![image](https://user-images.githubusercontent.com/60224159/185791829-4c9ac9d0-f29c-4be2-9dd8-2c538231bd24.png)

    - [x] true.
    - [ ] false.

10) To control the speed of a motor manually, one should use a/an ------------
    - [x] Electric Potentiometer.
    - [ ] Insulator.
    - [ ] Resistor.
    - [ ] Capacitor.

11) The following circuit, shows the operation of transistors as a switch with a current gain of hfE or Beta ? 

    ![image](https://user-images.githubusercontent.com/60224159/185792197-3be5200f-ce02-409a-98f4-92676f110fe4.png)

    - [x] true.
    - [ ] false.

    Where Beta or hFE equals : 
    - [x] the gain ratio between Ic and IB.
    - [ ] the gain ratio between Ie and IB.
    - [ ] the gain ratio between Ic and GND.

12) Which of the following equations is used for calculating the minimum base current I(B) required for the NPN to act as an AND gate (a switch) ?

    ![image](https://user-images.githubusercontent.com/60224159/185792197-3be5200f-ce02-409a-98f4-92676f110fe4.png)
    
    `HINT: Apply the KVL on the loop BE and use the current gain equation hFE = I(C) / I(B) to substitute it in the equation I(E) = I(B) + I(C).`
    
    - [ ] (V'B' - V'BE') / (1 + hFE) . R(2).
    - [ ] (V'E') / (1 + hFE) . R(2).
    - [ ] (V'CE') / (1 + hFE) . R(2).
    - [x] A and B.
	
Answer: 
```
Since,

- V(B) = V(E) + V(BE), --(K.V.L)
- V(E) = I(E).R(E),    --(Ohm's Law)
- I(E) = I(B) + I(C),  --(K.C.L)
- I(C) = hFE * I(B).   --(Transistor current gain)

Then,

By substituting "I(C) = hFE * I(B)" in "I(E) = I(B) + I(C)": 
I(E) = I(B) + hFE * I(B) 
     = I(B) . (1 + hFE).

By substituting "I(E) = I(B) . (1 + hFE)" in " V(B) = V(E) + V(BE)", where; "V(E) = I(E) . R(E)":
V(B) = V(E) + V(BE) 
     = I(E) . R(E) + V(BE)
     = (I(B) . (1 + hFE)) . R(E) + V(BE)

V(B) - V(BE) = (I(B) . (1 + hFE)) . R(E) 

Then,

I(B) = V(B) - V(BE) / R(E) . (1 + hFE)   (Q.E.D)

```

--------------------------------------

## Embedded engineering principles questions:

1) What's the usage of the AND gate ? 

	- [ ] Adding 2 bytes together.
	- [ ] Subtracting 2 bytes from one another.
	- [x] Multiplying 2 bytes.
	- [ ] A and C.

2) What's the usage of the OR gate ? 

	- [ ] Adding 2 bytes togther.
	- [ ] Acts as an ON switch for a circuit with two logic values, if one of them is TRUE.
	- [ ] Multiplying 2 bytes.
	- [x] A and B.

3) What's the result of `0b00000010 + 0b000000010` ? 

	- [x] `0b00000100`
	- [ ] `0b00000110`
	- [ ] `0b00000011`
	- [ ] `0b00000111`

4) What's the result of `0b00000010 | 0b00000010` ?

	- [x] `0b00000010`
	- [ ] `0b00000110`
	- [ ] `0b00000011`
	- [ ] `0b00000111`

5) What's the result of `0b00000010 | 0b00000011` ?

	- [ ] `0b00000010`
	- [ ] `0b00000110`
	- [x] `0b00000011`
	- [ ] `0b00000111`

6) What's the result of `0b00000011 & 0b00000010` ? 

	- [x] `0b00000010`
	- [ ] `0b00000000`
	- [ ] `0b00000011`
	- [ ] `0b00000001`

7) What's the result of `A.B`, where A = 0b00001111 and B = 0b00000011 ? 

	- [x] `0b00000011`
	- [ ] `0b00001111`
	- [ ] `0b00001010`
	- [ ] `0b00000000`

8) How a computer subracts 2 bytes from one another ? 

	- [x] By taking the 2s complement of the subtrahend and adding them.
	- [ ] By taking the 1s complement of the minuend and adding them.
	- [ ] By taking the 1s complement of both bytes and adding them.
	- [ ] No right answer is provided here.

9) How a computer performs this operation (0b000000010 - 0b000000001) ? 
      
	```
	Answer: 
	By taking the 2s complement of the subtrahend (2nd digit), which is the 1s complement + 0b01
	1) Taking the 1s complement: ~0b000000001 = 0b111111110
	2) Adding 0b01: 0b111111110 + 0b01 = 0b111111111
	3) Adding the Minuend (1st digit) to the 2s complement of the subtrahend: 0b000000010 + 0b111111111 = 0b000000001
	```

10) The 1s complement of a byte -----------

	- [x] is taken by applying a NOT gate to the byte.
	- [ ] is taken by applying adding 0x01 to the byte.
	- [ ] is taken by applying an OR gate with 0x01.
	- [ ] none of the above.

11) The main usage of an OR gate is -----------

	- [x] adding 2 bytes together.
	- [ ] subtracting 2 bytes.
	- [ ] controlling high voltage cicuits.
	- [ ] none of the above.

12) Which of the following is the equivalent gate to N-XOR gate ? 

	- [ ] `~(...^...)`
	- [ ] `~((~(A) & B) | (A & ~B))`
	- [ ] `(...^...)`
	- [x] A and B

13) The following truth table is an example of ------------

	![image](https://user-images.githubusercontent.com/60224159/185800213-61b66af5-c062-48a1-8f9a-e221e9182cba.png)

	- [x] Flip-Flops.
	- [ ] AND-Gates.
	- [ ] OR-Gates.
	- [ ] NAND-Gates.

------------------------------------------------------------------

## Embedded basic C/C++: 

1) What's the output of this code: 
```c
#include<stdint.h>

#define TXEN 5
#define RXEN 6

const uint8_t ENABLE_RX_TX = (1 << RXEN) | (1 << TXEN);
printf("%i\n", ENABLE_RX_TX);
```
-
	- [x] 0b01100000
	- [ ] 0b00110000
	- [ ] 0b00010000
	- [ ] 0b00111000


2) What's the output of this code: 
```c
#include<stdio.h>
#include<stdint.h>

#define UDRE 1
#define UIEN 2
#define TXEN 5
#define RXEN 6

#define USCR ((uint8_t) (1 << TXEN) | (1 << UDRE) | (1 << UIEN))

#define isTxRxEnabled() ((uint8_t) (USCR & ((1 << TXEN) | (1 << RXEN))))

int main(void) {
	printf("%i\n", isTxRxEnabled());
return 0;
}
```
-
	- [x] 0b00100000
	- [ ] 0b01100000
	- [ ] 0b00100011
	- [ ] 0b01000000


3) What's the output of this code: 
```c
#include<stdio.h>
#include<stdint.h>

#define UDRE 1
#define UIEN 2
#define TXEN 5
#define RXEN 6

#define TxRxEnabledBit ((const uint8_t) ((1 << TXEN) | (1 << RXEN)))

volatile uint8_t USCR = ((uint8_t) (1 << UDRE) | (1 << UIEN));

static inline uint8_t setBitEnabled(volatile uint8_t* CSR, const uint8_t ENABLE_BIT) {
	return *CSR |= ENABLE_BIT;
} 

int main(void) {   

    setBitEnabled(&USCR, TxRxEnabledBit);
    printf("%i", USCR);

    return 0;
}
```
-
	- [ ] 0b00000000
	- [x] 0b01100110
	- [ ] 0b01100000
	- [ ] 0b01000110
	
4) What's the output of this code ? 
```c
#include<stdio.h>
#include<stdint.h>

#define UDRE 1
#define UIEN 2
#define TXEN 5
#define RXEN 6

#define TxRxDisabledBit ~((const uint8_t) ((1 << TXEN) | (1 << RXEN)))

volatile uint8_t USCR = ((uint8_t) (1 << UDRE) | (1 << UIEN) | (1 << RXEN) | (1 << TXEN));

static inline uint8_t setBitDisabled(volatile uint8_t* CSR, const uint8_t DISABLE_BIT) {
	return *CSR &= DISABLE_BIT;
} 

int main(void) {

    setBitDisabled(&USCR, TxRxDisabledBit);
    printf("%i", USCR);

    return 0;
}
```
-
	- [ ] 0b00000000
	- [x] 0b00000110
	- [ ] 0b01100000
	- [ ] 0b01000110

5) What's the difference between `union` and `struct` C structures ? 

	```
	Answer: 
	A structure contains an ordered group of data objects. Unlike the elements of an array, the data objects
	within a structure can have varied data types. Each data object in a structure is a member or field.
	
	A union is an object similar to a structure except that all of its members start at the same location in
	memory. 
	A union variable can represent the value of only one of its members at a time.
	```

6) What's the main usage of C structs ? 

	```
	Answer: 
	For representing a group of data with varied data types or an object structure 
	with members/fields outside of classes hierarchy logic.
	```

7) Write a pseudo-code for this SPI diagram in C or C++ or java with pulse width = 230ns.

	![image](https://user-images.githubusercontent.com/60224159/185855592-ffbf376f-3e8b-4f49-97d2-c00d456ccdfa.png)

	For C/C++: add `#include<SPI.h>` and use already defined bits `CS, SCK` all lies on PORTB and `SPDR` register.
	
	For java: add `import com.avr.spi.Datalines;` and use already defined fields `Datalines.CS.value`, `Datalines.SCK.value` all lies on `com.avr.spi.Register.PORTB` and `com.avr.spi.Register.SPDR` a R/W register.

	[C/C++]
	```c
	#include<stdint.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<avr/io.h>
	#include<util/delay.h>
	#include<SPI.h>

	#define SDI 0xef

	static inline void setCSHigh() {
	   /* bring CS or SS to high to end this slave communication */
	    PORTB |= (1 << CS);	
	}

	static inline void setCSLow() {
	   /* bring CS or SS to low to start this slave communication */
	    PORTB &= ~(1 << CS);
	}

	static inline void setMOSIData(const uint8_t* data) {
	    SPDR = *data;
	}

	static inline volatile uint8_t* getMISOData() {
	    return &SPDR;
	}

	static inline void generateSCLK(const uint32_t count, const uint8_t width) {
	    for (uint32_t i = 0; i < count; i++) {
		PORTB &= ~(1 << SCK);
		_delay_us(width / 1000);
		PORTB |= (1 << SCK);
		_delay_us(width / 1000);
	    }
	}

	int main(void) {
	    volatile uint8_t* buffer = (uint8_t*) calloc(1, sizeof(uint8_t));

	    setCSLow();
	    /* send the data register address */
	    setMOSIData(SDI);
	    /* clock out the address to the slave */
	    generateSCLK(8, 230);
	    /* clock in the data register to the master */
	    generateSCLK(8, 230);

	    buffer = getMISOData();

	    printf("%i", *buffer);

	return 0;
	}

	```
	[java]
	```java
	package com.avr.examples;

	import com.avr.spi.Datalines;
	import com.avr.spi.Register;
	import java.lang.InterruptedException;
      
	public class TestSPI {

		private static final int SDI = 0xef;

		private static void setCSHigh() {
		    /* bring CS or SS to high to end this slave communication */
		    Register.PORTB |= (1 << Datalines.CS); 
		}

		private static void setCSLow() {
		    /* bring CS or SS to low to start this slave communication */
		    Register.PORTB &= ~(1 << Datalines.CS); 
		}

		private static void setMOSIData(final int data) {
		    Register.SPDR = data;
		}

		private static int getMISOData() {
		    return Register.SPDR;
		}

		private static void generateSCLK(final int count, final int width) throws InterruptedException {
		    for (int i = 0; i < count; i++) {
			Register.PORTB &= ~(1 << Datalines.SCK);
			Thread.sleep(width / Math.pow(10, 6));
			Register.PORTB |= (1 << Datalines.SCK);
			Thread.sleep(width / Math.pow(10, 6));
		    }
		}

		public static void main(String args[]) throws InterruptedException {
		    final Object[] buffer = new Object[1];

		    setCSLow();
		    /* send the data register address */
		    setMOSIData(SDI);
		    /* clock out the address to the slave */
		    generateSCLK(8, 230);
		    /* clock in the data register to the master */
		    generateSCLK(8, 230);

		    buffer[0] = getMISOData();

		    System.out.println(buffer[0]);

		}
	}
	```
