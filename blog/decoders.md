# Binary Decoders
> Created by [Pavly G.](https://github.com/Scrappers-glitch)

Binary decoders are combinatorial logic circuits in which a group of inputs (n) can control the logic state of a group of outputs (m); where (n) is the number of inputs and (m) is the number of outputs and `(m <= 2^n)`.

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
