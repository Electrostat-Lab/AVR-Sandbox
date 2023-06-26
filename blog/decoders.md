# Binary Decoders
> Created by [Pavly G.](https://github.com/Scrappers-glitch)

Binary decoders are combinatorial logic circuits in which a group of inputs (n) can control the logic state of a group of outputs (m); where (n) is the number of inputs and (m) is the number of outputs such that `(m <= 2^n)`.

Binary decoders can be constructed from: 
1) NOT Gates (inverters).
2) Central data-lines.
3) AND (for active "HIGH" output) or NAND (for active "LOW" outputs) Gates.

This is a basic circuit of a `2-to-4 binary decoder`:

![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/348edade-6bc9-42a1-a46f-970b29102dc9)


The truth table of this circuit can be displayed as follows: 

| A | B | Q0 | Q1 | Q2 | Q3 | 
|---|---|----|----|----|----|
| 0 | 0 | 1 | 0 | 0 | 0 |   
| 0 | 1 | 0 | 1 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 |
| 1 | 1 | 0 | 0 | 0 | 1 |

Usages of binary decoders:
1) Selectively activates and de-activates chips based on a provided address.
2) Controlling high voltage circuits by activitating and de-activating them through a transistor circuit.
3) Data routing in memory chips programming.

The 74LS138 Binary Decoder is one of the most useful `3-to-8 binary decoders` that is used as Address Decoders.

## Cracking the 74LS138 Datasheet

74LS138 is a 3-to-8 binary decoder/demultiplexer with 3 enable input lines.

This is the internal circuitry for `74LS138 Binary Decoder`:

| Connection Diagram | Logic Diagram | 
|--------------------|---------------|
| ![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/26302203-d0fe-4064-98bb-28f5aac73c77) | ![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/1f51613e-3d89-4dc2-abc0-b8cf92f4285d) |   

The main components of 74LS138 are Inverters and NAND Gates, other parts of construction are constructed using common data-lines.

The combinatoric digital circuit shows that 3-input data lines can be decoded into 8-output data lines, by inserting common data-lines (marked by green) before and after (marked by red triangles) the inverter gates reducing the need to use more input lines.

The DM74LS138 decodes one-of-eight lines, based upon
the conditions at the three binary select inputs and the
three enable inputs.

> Note: The DM74LS138 decodes one-of-eight lines, based upon
> the conditions at the three binary select inputs and the
> three enable inputs.
>
> Note: The DM74LS139 comprises two separate two-line-to-four-
> line decoders in a single package. The active-low enable
> input can be used as a data line in demultiplexing applications.
> 

-------------------
## Examples on decoding addresses: 

The following circuit is a (4k x 8) memory chip with 12 Address pins (A0-A11) representing (2^12) corresponding memory locations with 8 data pins (D0-D7) indicating input/output of 8-bits for the selected memory location, the MSB (Most Significant Bits) A12-A13-A14 selects this memory chip among others by bringing the CS to active LOW:

![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/130e94b6-5006-4425-b9a1-33a4de53b363)

Color codes: 
1) Green Data lines: represents the MSBs of the memory address, these bits define which memory chip will be selected.
2) Light-Red Data lines: represents Address Data lines, these bits define which memory location will be involved in the I/O operation when this chip is selected.
3) Dark-Red Data lines: represents I/O data lines, 8 I/O pins corresponding to a parallel input of 8-bits for the currently active memory location in this memory chip.

> The total storage (4k x 8) bits can be calculated using the following equation:
> 2^12 Memory Locations (A0-A11) x 8-bits for each = 4K x 8 bits.

-------------------
## Constructing Boolean Functions

Boolean functions can be constructed using additional logic gates on the output side of decoders, for example: 

![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/d0a115b8-fb13-4147-867a-1ca3ae2cd1aa)

This circuit corresponds to this boolean function: 

![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/56dfabef-2025-4c18-84e4-6e270260f93d)

-----------------------------
## Cascading Decoder Circuits

Cascading decoders aims at magnifying the number of input lines for a desired decoder with some available stock decoders.

For example, it's possible to construct a `4-to-16 binary decoder` with a `3-to-8 binary decoder` by introducing 2 binary decoders, the number of the `3-to-8 binary decoders` to utilize in this circuit can be calculated using this equation: 
`2^(N-n)`; where [N] is the number of input lines of the desired decoder (the 4-to-16 decoder) and [n] is the number of the input lines of the available decoder (the 3-to-8 decoder).

Here is the circuit diagram of the cascade construction: 

![image](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/assets/60224159/7c5034b7-291b-44d2-9c03-7c0b1ac9cdbe)

This logic circuit will have up-to (2^4) or 16 different combinational inputs that will be decoded into 16-bits of output, the (D) input line selects which decoder will be activated, (0) to select the first decoder aka. the least significant decoder for the least significant 8-bits, while the (1) input at (D) selects the second decoder aka. the most significant decoder for the most significant 8-bits.

-----------------------------

## Resources: 
- [Electronics Tutorial: Binary Decoders](https://www.electronics-tutorials.ws/combination/comb_5.html)
- [Digital Electronics: Principles, Devices and Applications by Anil K. Maini](https://www.wiley.com/en-us/Digital+Electronics%3A+Principles%2C+Devices+and+Applications-p-9780470510513)
- [AVR Microcontroller and Embedded Systems: Using Assembly and C](https://www.pearson.com/store/p/avr-microcontroller-and-embedded-systems-pearson-new-international-edition-pdf-ebook/GPROG_A100061251868_learnerau-availability/9781292054339)
