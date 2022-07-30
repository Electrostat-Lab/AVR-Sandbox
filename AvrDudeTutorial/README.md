# Avrdude Tutorial

<a name="TOPICS"></a>
## Topics covered: 
1) What's `avrdude` ?
2) `avrdude` basic commands.
3) `avrdude` in shell scripts.
4) `avrdude` in makefile scripts.
------------------------------------------------------

## 1) What's `avrdude` ? [--Jump to Topics--](#TOPICS)

Avrdude: is a program for downloading and uploading the on-chip memories of Microchip’s AVR microcontrollers. 
It can program the Flash and EEPROM, and where supported by the programming protocol, it can program fuse and lock bits. 
AVRDUDE also supplies a direct instruction mode allowing one to issue any programming instruction to the AVR chip regardless of whether AVRDUDE implements that specific feature of a particular chip.

-----------------------------------------------------

## 2) `avrdude` basic commands: [--Jump to Topics--](#TOPICS)

- Start off by installing avrdude from the apt:
```sh
sudo apt-get install avrdude
```
- Connect your mcu to the PC and open the avrdude terminal to fetch the details of the connected chip and program fuse bits:
```sh
sudo avrdude -p${MCU_ALIAS} -P${PORT} -b{BAUD_RATE} -c${PROGRAMMER} -t
```
- Those are the commands for the avrdude terminal mode operation: 

| `Commands I` | `Commands II` |
|-------------|----------------|
| 

- Examples: 
```sh
pavl@pavl-machine:/home/twisted/GradleProjects/AVR-Sandbox$ sudo avrdude -p m328p -c arduino -b57600 -P'/dev/ttyUSB0' -t

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude> part
>>> part 

AVR Part                      : ATmega328P
Chip Erase delay              : 9000 us
PAGEL                         : PD7
BS2                           : PC2
RESET disposition             : dedicated
RETRY pulse                   : SCK
serial program mode           : yes
parallel program mode         : yes
Timeout                       : 200
StabDelay                     : 100
CmdexeDelay                   : 25
SyncLoops                     : 32
ByteDelay                     : 0
PollIndex                     : 3
PollValue                     : 0x53
Memory Detail                 :

                         Block Poll               Page                       Polled
  Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
  ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
  eeprom        65    20     4    0 no       1024    4      0  3600  3600 0xff 0xff
  flash         65     6   128    0 yes     32768  128    256  4500  4500 0xff 0xff
  lfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
  hfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
  efuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
  lock           0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
  calibration    0     0     0    0 no          1    0      0     0     0 0x00 0x00
  signature      0     0     0    0 no          3    0      0     0     0 0x00 0x00

avrdude> 
```

