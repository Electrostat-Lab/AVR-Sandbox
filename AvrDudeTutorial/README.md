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

| `Commands I` | `Commands II` | `Commands III` |
|-------------|----------------|---------------|
| ![image](https://user-images.githubusercontent.com/60224159/181906807-1a651c84-72c4-4692-9051-61c2831ac488.png) | ![image](https://user-images.githubusercontent.com/60224159/181906839-e016f192-ce0e-4f16-b0ac-6ccfa3ce53c4.png) | ![image](https://user-images.githubusercontent.com/60224159/181906861-f2579e89-62ba-4512-a807-17fe65d3f6f9.png) |

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
- For more refer to the [documentation-file]().
- To flash a `.hex` file use the -U with flash option: 
```sh
sudo avrdude -c ${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS} -F -U flash:w:${output}'.hex'
```
- The `[-F] Option`: Normally, AVRDUDE tries to verify that the device signature read from the
part is reasonable before continuing. Since it can happen from time to time that
a device has a broken (erased or overwritten) device signature but is otherwise
operating normally, this options is provided to override the check. Also, for
programmers like the Atmel STK500 and STK600 which can adjust parameters
local to the programming tool (independent of an actual connection to a target
controller), this option can be used together with -t to continue in terminal
mode.
- Examples:
```sh
pavl@pavl-machine:/home/twisted/GradleProjects/AVR-Sandbox$ sudo avrdude -c'arduino' -b'57600' -P'/dev/ttyUSB0' -p'm328p' -F -U flash:w:'firmware.hex'

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "/home/twisted/GradleProjects/AVR-Sandbox/firmware.hex"
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/firmware.hex auto detected as Intel Hex
avrdude: writing flash (3022 bytes):

Writing | ################################################## | 100% 0.90s

avrdude: 3022 bytes of flash written
avrdude: verifying flash memory against /home/twisted/GradleProjects/AVR-Sandbox/firmware.hex:
avrdude: load data flash data from input file /home/twisted/GradleProjects/AVR-Sandbox/firmware.hex:
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/firmware.hex auto detected as Intel Hex
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/firmware.hex contains 3022 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.68s

avrdude: verifying ...
avrdude: 3022 bytes of flash verified

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.
```
------------------------------------------------------------------
## 3) `avrdude` in shell scripts: [--Jump to Topics--](#TOPICS)

Use some variables in a source `variables.sh` and an `upload` function as follows: 
- `variables.sh`:
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
BAUD_RATE='57600'
PORT='/dev/ttyUSB0'
CHIP='atmega328p'
CHIP_ALIAS='m328'
PROGRAMMER='arduino'
# Common Variables contain colors
source ${rootProject}'/CommonVariables.sh'
source ${rootProject}'/AVR__HOME.sh'
output=${project}'/output/'${clibName}
```
- `upload.sh`: 
```sh
source variables.sh

function upload() {
	sudo avrdude -c ${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS} -F -U flash:w:${output}'.hex'
	return $?
}

echo -e "${WHITE_C} --MajorTask@UploadingCode : Uploading Hex file"
if [[ ! `upload` -eq 0 ]]; then
	echo -e "${RED_C} --MajorTask@UploadingCode : Failed to upload hex file, exits with errno700."
	exit 700
else 
	echo -e "${GREEN_C} --MajorTask@UploadingCode : Task finished."
fi
echo -e ${RESET_Cs}
```
For more, refer to the [shell-build]() folder.

-----------------------------------------------------------

## 4) `avrdude` in makefile scripts: [--Jump to Topics--](#TOPICS)

General Syntax of GNU Makefile: 
```makefile
# define common variables here
variableA = 'Hello World'
variableB = `echo 'Hey'`

# define some shell functions 

# define set of rules
targetA: command ${variableB}
	 command
	 command

targetB: command2 ${variableA}

targetC: targetB

all: targetA targetB targetC
```
To run, make a target: 
```sh
make targetA
```
```sh
make all
```
and so on....

1) Create a makefile as follows with these variables in place: 
```makefile
# CHIP Charachteristics
CHIP_ALIAS = m328p
PROGRAMMER = arduino
BAUD_RATE  = '57600'
PORT       = '/dev/ttyUSB0'
CHIP       = 'atmega328p'
AVR_DUDE   = avrdude -c ${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS}
```
2) Place the above shell scripts inside `./AvrDudeTutorial/makefile-build/shell-build/`, with the following final directory tree: 
```sh
├── Makefile
└── shell-build
    ├── compile.sh
    ├── upload.sh
    └── variables.sh

1 directory, 4 files
```
3) Create some set of rules to make, and reference shell scripts source from those makefile rules:
```makefile
# Map shell commands to some makefile set of rules

compile: 
	source 'shell-build/compile.sh'

upload: 
	source 'shell-build/upload.sh'

terminal-mode: 
	sudo ${AVR_DUDE} -t

build: compile upload
```
4) Run a target rule using `make $target` command, examples: 

- Building project example [Compile + Upload]:
```sh
$ make build 
source 'shell-build/compile.sh'
 --MajorTask@Compile : Compiling the project

 --MajorTask@Compile : Compilation succeeded.

 --MajorTask@Hexing : Creating Hex file
 --MajorTask@Hexing : Hex file created successfully.

source 'shell-build/upload.sh'
 --MajorTask@UploadingCode : Uploading Hex file

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: Expected signature for ATmega328 is 1E 95 14
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "/home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex"
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: writing flash (324 bytes):

Writing | ################################################## | 100% 0.11s

avrdude: 324 bytes of flash written
avrdude: verifying flash memory against /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: load data flash data from input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex contains 324 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.09s

avrdude: verifying ...
avrdude: 324 bytes of flash verified

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.

 --MajorTask@UploadingCode : Task finished.
```
- Compile only example:
```sh
$ make compile 
source 'shell-build/compile.sh'
 --MajorTask@Compile : Compiling the project

 --MajorTask@Compile : Compilation succeeded.

 --MajorTask@Hexing : Creating Hex file
 --MajorTask@Hexing : Hex file created successfully.
```

- Upload only example: 
```sh
$ make upload 
source 'shell-build/upload.sh'
 --MajorTask@UploadingCode : Uploading Hex file

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: Expected signature for ATmega328 is 1E 95 14
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "/home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex"
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: writing flash (324 bytes):

Writing | ################################################## | 100% 0.11s

avrdude: 324 bytes of flash written
avrdude: verifying flash memory against /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: load data flash data from input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex contains 324 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.09s

avrdude: verifying ...
avrdude: 324 bytes of flash verified

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.

 --MajorTask@UploadingCode : Task finished.
```

- The terminal-mode example using GNU makefile:
```sh
$ make terminal-mode 
sudo avrdude -c arduino -b'57600' -P'/dev/ttyUSB0' -pm328p -t

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
- Compile, upload and then open terminal-mode: 
```sh
$ make build terminal-mode 
source 'shell-build/compile.sh'
 --MajorTask@Compile : Compiling the project

 --MajorTask@Compile : Compilation succeeded.

 --MajorTask@Hexing : Creating Hex file
 --MajorTask@Hexing : Hex file created successfully.

source 'shell-build/upload.sh'
 --MajorTask@UploadingCode : Uploading Hex file

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: Expected signature for ATmega328 is 1E 95 14
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "/home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex"
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: writing flash (324 bytes):

Writing | ################################################## | 100% 0.11s

avrdude: 324 bytes of flash written
avrdude: verifying flash memory against /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: load data flash data from input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex:
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex auto detected as Intel Hex
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/AvrDudeTutorial/output/libHelloBlink.hex contains 324 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.08s

avrdude: verifying ...
avrdude: 324 bytes of flash verified

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.

 --MajorTask@UploadingCode : Task finished.

sudo avrdude -c arduino -b'57600' -P'/dev/ttyUSB0' -pm328p -t

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude> 
```
- For more refer to the [GNU Makefile Docs Page](https://www.gnu.org/software/make/manual/make.html) and [GNU Makefile by example](https://makefiletutorial.com/#getting-started).
