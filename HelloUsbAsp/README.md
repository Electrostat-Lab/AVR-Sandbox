## HelloUsbAsp

Demonstrates the usage of the blink example on a simple 9v 300 mAmp circuit for the Atmega32.

<a name="TOPICS"></a>
Topics Covered: 
1) Circuit Components.
2) Calculating the protective resistance.
3) Finding the resistance color code.
4) Calculating Max Power Consumption and comparing the state with different current draws.
5) Circuit Connection.
6) Testing Output.
7) Live testing session.

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

Before calculating the resistor value, take note of the max device ratings: 

![image](https://user-images.githubusercontent.com/60224159/178972280-f2d97075-09da-4fff-85aa-b30b2872a0a0.png)


By using Kirchhoff's voltage law (KVL) on this closed circuit voltage uint and the above image shows the Max DC Current = 200mAmps:
- E(V) = V(reg) + V(at) + V(r) = 0; where E -> Summation, V(reg) -> Regulator output, V(at) -> Atmega max required voltage, V(r) -> Protective resistor voltage drop.
- 6v - 5.5v - `I(max).r` = 0
- 6v - 5.5v - `(200 * (10^-3)).r` = 0, by substituting `I` with `300mAmps`(depending on your power supply/Battery ratings)
- 6v - 5.5v - `0.2 * r` = 0
- 0.5v - `0.2 * r` = 0
- (-`0.2 * r`) = -0.5v
- r = 0.5volts / 0.2amps = 2.5 = 3 OHMS.

---------------OR--------------- 

- V(reg) = V(at) + V(r); where V(reg) -> Regulator output, V(at) -> Atmega required voltage, V(r) -> Protective resistor voltage drop.
- 6v = 5.5v + `I(max).r`
- 6v = 5.5v + `(200 * (10^-3)).r`, by substituting `I` with `200mAmps`(Max DC current ratings).
- 6v = 5.5v + `(0.2 * r)`
- r = (6 - 5.5)volts / 0.2amps = 2.5 = 3 OHMS.

![image](https://user-images.githubusercontent.com/60224159/178731499-76d59b5d-6beb-44a6-9e8b-665df1bc34cd.png)

------------------------------

## 3) Finding the resistance color code: 

| Use this table provided by [ElectronicsTutorial.com](https://www.electronics-tutorials.ws/resistor/res_2.html) |
|---------------------------------------------------------------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/179056363-290002a6-6b84-4ecc-ba06-afcfd985db67.png) |

| A table for different banded resistors |
|----------------------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/178738625-bc8967f5-bd24-4ef6-bee7-bbabace0464d.png) |

In this case we are using the 4 banded resistors, so to find a 2 OHM resistor, those can be the color codes: 
- 3 OHM = 03 * 1 +/- 0.05 ===> `BLACK`-`GOLD`-`BLACK`-`GREY`
- 3 OHM = 30 * 0.1 +/- 0.05 ===> `GOLD`-`BLACK`-`LIGHT GOLD`-`GREY`

| Notes |
|--------------------|
| **Resistor tolerance** is a measure of the resistors variation from the specified resistive value and is a consequence of the manufacturing process and is expressed as a percentage of its “nominal” or preferred value.
Typical resistor tolerances for film resistors range from 1% to 10% while carbon resistors have tolerances up to 20%. Resistors with tolerances lower than 2% are called precision resistors with the or lower tolerance resistors being more expensive. |

-----------------------------------
## 4) Calculating Max Power Consumption and comparing the state with different current draws: [--Jump to Topics--](#TOPICS) 

| `Power Consumption at max current draw 200mAmps` | `Power Consumption at 45mAmps current draw` | `Power Consumption at 20mAmps current draw` |
|--------------------------|--------------------------------------|--------------------------------------|
| P(max) = V * I(max) = 5.5 * 200mamps = 5.5 * 0.2 = 1.1 watt. | P = (6 - (0.045 * 3 OHMS)) * 45mAmps = 5.865 * 45mamps = 5.865 * 0.045 = 0.2639 watt. | P = (6 - (0.020 * 3 OHMS)) * 20mAmps = 5.94 * 0.02 = 0.1188 watt. |

Those different measurements are the result of using different current draws at the same supply voltage (6v) and the same resistance (3 OHMS or 4 OHMS).

So, we are safe as long as we don't exceed the max wattage for the device

--------------------------

## 5) Circuit Connection: [--Jump to Topics--](#TOPICS) 

Now connect your circuit as shown in this diagram:

| `Circuit Diagram` | `Measuring Input Voltage in volts` | `Measuring Input Current in milli-amps` |
|-------------------|---------------|---------------------------------------|
| ![](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloUsbAsp/fritzing/UsbAsp%20External%20Circuit.png) | ![Circuit](https://user-images.githubusercontent.com/60224159/179304213-e71b3e0f-1654-4e60-8875-3d219d3f2283.jpg) | ![Current Draw](https://user-images.githubusercontent.com/60224159/179313199-ef56e13c-48a9-49fb-b8fd-aff108e39f91.jpg) |

-------------------------------------

## 6) Testing Output: [--Jump to Topics--](#TOPICS) 

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

## 7) Live testing session: 

[![Video](https://user-images.githubusercontent.com/60224159/179325781-8e4e1148-c190-4fd8-9b6b-214881f1fb38.jpg)](https://www.linkedin.com/embed/feed/update/urn:li:ugcPost:6953830384706953216)

