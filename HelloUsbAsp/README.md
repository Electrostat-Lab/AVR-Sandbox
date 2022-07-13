## HelloUsbAsp

Demonstrates the usage of the blink example on a simple 9v 300 mAmp circuit for the Atmega32.

<a name="TOPICS"></a>
Topics Covered: 
1) Circuit Components.
2) Calculating the protective resistance.
3) Finding the resistance color code.
4) Circuit Connection.
5) Testing Output.
6) Live testing session.

--------------

## 1) Circuit Components: [--Jump to Topics--](#TOPICS)
- 1 x Atmega32 chip.
- 1 x UsbAsp Fares PCB.
- 1 x Multimeter.
- 1 x Battery 9v (I-mamps).
- 1 x LM7806CV Voltage regulator.
- 1 x Ohm resistor (R-Ohms).
- 1 x Bush button.
- 1 x 3v3 LED.
- Female-Male and Male-Male Jumper wires.
- Briding wires (optional).
- A Breadboard.

---------------

## 2) Calculating the protective resistance: [--Jump to Topics--](#TOPICS)

By using Kirchhoff's voltage law (KVL) on this closed circuit voltage uint: 
- E(V) = V(reg) + V(at) + V(r) = 0; where E -> Summation, V(reg) -> Regulator output, V(at) -> Atmega required voltage, V(r) -> Protective resistor voltage drop.
- 6v - 5.5v - `I.r` = 0
- 6v - 5.5v - `(300 * (10^-3)).r` = 0, by substituting `I` with `300mAmps`(depending on your power supply/Battery ratings)
- 6v - 5.5v - `0.3 * r` = 0
- 0.5v - `0.3 * r` = 0
- (-`0.3 * r`) = -0.5v
- r = 0.5volts / 0.3amps = 1.666666667 = 2 OHMS.

---------------OR--------------- 

- V(reg) = V(at) + V(r); where V(reg) -> Regulator output, V(at) -> Atmega required voltage, V(r) -> Protective resistor voltage drop.
- 6v = 5.5v + `I.r`
- 6v = 5.5v + `(300 * (10^-3)).r`, by substituting `I` with `300mAmps`(depending on your power supply/Battery ratings)
- 6v = 5.5v + `(0.3 * r)`
- r = (6 - 5.5)volts / 0.3amps = 1.666666667 = `2 OHMS`.

![image](https://user-images.githubusercontent.com/60224159/178731499-76d59b5d-6beb-44a6-9e8b-665df1bc34cd.png)

------------------------------

## 3) Finding the resistance color code: 

| Use this table provided by [ElectronicsTutorial.com](https://www.electronics-tutorials.ws/resistor/res_2.html) |
|---------------------------------------------------------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178738049-cf5703a9-b7bc-4594-aed5-53b83365ff20.png) |

| A table for different banded resistors |
|----------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178738625-bc8967f5-bd24-4ef6-bee7-bbabace0464d.png) |

In this case we are using the 4 banded resistors, so to find a 2 OHM resistor, those can be the color codes: 
- 2 OHM = 02 * 1 +/- 0.05 ===> `BLACK`-`RED`-`BLACK`-`GREY`
- 2 OHM = 20 * 0.1 +/- 0.05 ===> `RED`-`BLACK`-`GOLD`-`GREY`

| Notes |
|--------------------|
| **Resistor tolerance** is a measure of the resistors variation from the specified resistive value and is a consequence of the manufacturing process and is expressed as a percentage of its “nominal” or preferred value.
Typical resistor tolerances for film resistors range from 1% to 10% while carbon resistors have tolerances up to 20%. Resistors with tolerances lower than 2% are called precision resistors with the or lower tolerance resistors being more expensive. |

-----------------------------------

## 4) Circuit Connection: [--Jump to Topics--](#TOPICS) 

Now connect your circuit as shown in this diagram:

| `Circuit Diagram` | `Example` | 
|-------------------|---------------|
| ![UsbAsp External Circuit](https://user-images.githubusercontent.com/60224159/178742853-7bbd3b38-c829-4571-a11c-7d7f2aeb9108.png) | ![Circuit](https://user-images.githubusercontent.com/60224159/178741890-240ddcd1-03c8-42e7-8715-6c9f49e79189.jpg) |

-------------------------------------

## 5) Testing Output: [--Jump to Topics--](#TOPICS) 

Now, connect your usbasp using the above circuit (don't forget to connect the SPI of the usbasp GND to the COM) and change the `variables.sh` to this:

```sh
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

clibName=('libHelloBlink')
# AVR-DUDE properties
BAUD_RATE='9600'
PORT='/dev/ttyUSB0'
CHIP='atmega32'
CHIP_ALIAS='m32'
PROGRAMMER='usbasp'
# Common Variables contain colors
source ${rootProject}'/CommonVariables.sh'
source ${rootProject}'/AVR__HOME.sh'
output=${project}'/output/'${clibName}
```

Connect the usbasp and start flashing..............
