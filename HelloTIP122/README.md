# HelloTIP122
> Created by [Pavly G.](https://github.com/Scrappers-glitch)

A showcase for the use of TIP122 with the avr GPIO.

## Topics Covered: 
1) TIP122 Electrical Characteristics.

2) TIP122~AtMega32A Connection.

3) Calculating the circuit characteristics.

## 1) TIP122 Electrical Charachteristics:

| `Absolute Maximum Ratings` | `Electrical charachteristics Test` |
|----------------------------|------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/180226967-034a6a94-676a-455d-a89f-e1e171e80017.png) | ![image](https://user-images.githubusercontent.com/60224159/180226447-350736b2-57ef-483a-b059-92b50c5ce1d8.png) |

## 2) TIP122~AtMega32A Connection: 

This image illustrates the connection between atmega32A GPIO PB2 and TIP122 Base terminal: 

![TIP122Avr](https://user-images.githubusercontent.com/60224159/180228253-89838745-b30d-47c8-9952-fdf5be52a777.png)

## 3) Calculating the circuit characteristics:

![image](https://user-images.githubusercontent.com/60224159/180249500-363d53cd-7ba7-4782-b400-b1acdfe15f79.png)

1-Calculating the suitable resistor for the 1v7 RED LED: 
```
Using KVL (Kirchhoff's Voltage Law): 
Vcc = V1 + V2 + ....
Vcc = V(LED) + V(RL) + V(CE)
9v = 1v7 + I(c) . R(L)
; Let, I(c) = I(LED-max) = 20mAmps = 20/1000 = 0.02 amps.

Then, 
R(L) = (9v - 1v7) / 0.02amps = 365 OHMS.
```
2-Calculating the total I(c) Current draw when connecting the circuit at the CE terminal: 

From these findings: 

| `Voltage Drop across the load resistor "RL"` | `Amperage Reading across the CE terminal using the above circuit (I(C))` |
|---------------------------------------------|---------------------------------------------|
| ![PXL_20220721_222209195](https://user-images.githubusercontent.com/60224159/180334062-fa480d60-94f3-4609-8b9a-7245c4e1fbfc.jpg) | ![PXL_20220721_222833706](https://user-images.githubusercontent.com/60224159/180334197-dd721599-d26b-42b7-b81f-b82b2d323712.jpg) |

```
Using Ohm's Law (I = V/R), find the battery current draw (not the same as I(c)) at the CE circuit: 
I(draw) = V(RL) / R(L) 
     = 4v25 / (330 OHMS) = 0.01288 amps.
```
```
Finding the BETA (Current Gain) value constructed by this circuit: 
- Remove the LED and the Load Resistance as they limit the current draw affecting the I(C) and the recording.
- Calculate I(B) and I(C) and plug them into this equation:
> B = I(C) / I(B) = 0.1amps / 0.8mAmps = 0.1 / (0.8 / 1000) = 125.
```
The `TIP122` Darlington can provide over 1000 hFE as a current gain using the proper current at both the CE circuit and the BE circuit.

