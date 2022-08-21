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
V(B) = V(E) + V(BE), where V(BE) = 0.6 --(KVL)--

then, V(E) = V(B) - 0.6 = 5v0 - 0v6 = 4v4.

Since, I(E) = I(B) + I(C), V(E) = 4v4, I(C) = hFE * I(B) --(KCL)--

then, I(E) = I(B) + hFE . I(B) = I(B) . (1 + hFE).

==> I(B) = I(E) / (1 + hFE), I(E) = V(E) / R(2)

==> I(B) = V(E) / (1 + hFE) . R(2)
	 = 4v4 / (1 + hFE) . R(2) 
	 where R(2) is the total resistance value for the CE circuit and hFE is the current gain for the 
         transistor. 
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

	Answer: 
	By taking the 2s complement of the subtrahend (2nd digit), which is the 1s complement + 0b01
	1) Taking the 1s complement: ~0b000000001 = 0b111111110
	2) Adding 0b01: 0b111111110 + 0b01 = 0b111111111
	3) Adding the Minuend (1st digit) to the 2s complement of the subtrahend: 0b000000010 + 0b111111111 = 0b000000001

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
	- [ ] A and B

13) The following truth table is an example of ------------

	![image](https://user-images.githubusercontent.com/60224159/185800213-61b66af5-c062-48a1-8f9a-e221e9182cba.png)

	- [x] Flip-Flops.
	- [ ] AND-Gates.
	- [ ] OR-Gates.
	- [ ] NAND-Gates.

------------------------------------------------------------------

## Embedded basic C/C++: 
