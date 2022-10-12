# HelloMPLab.X IDE

This example shows an example of an atmega32A program using Microchip MPLab.X IDE.

Here is a general layout of the file tree:
```shell
┌─[pavl-machine@pavl-machine]─[/home/twisted/GradleProjects/AVR-Sandbox]
└──╼ $tree ./HelloMPLab.X/
./HelloMPLab.X/
├── build
│   └── default
│       └── production
│           ├── HelloWorld.o
│           └── HelloWorld.o.d
├── debug
│   └── default
├── dist
│   └── default
│       └── production
│           ├── HelloMPLab.X.production.elf
│           ├── HelloMPLab.X.production.hex
│           └── HelloMPLab.X.production.map
├── HelloWorld.c
├── Makefile
└── nbproject
    ├── configurations.xml
    ├── Makefile-default.mk
    ├── Makefile-genesis.properties
    ├── Makefile-impl.mk
    ├── Makefile-local-default.mk
    ├── Makefile-variables.mk
    ├── private
    │   ├── configurations.xml
    │   └── private.xml
    └── project.xml

10 directories, 16 files

```
The `Makefile` contains the main targets for exceuting the main GNU make implementation suffix rules (eg: .build-post) and the main rules recipe execute direct linux commands (eg: .build-impl) to clean, build, upload and/or clobber (which removes the directory of production), the variables for these linux/make commands are defined within `Makefile-variables.mk`.

Here is the makefile basic target, rules and recipes syntax:
```makefile
targets : prerequisites
recipe
...
```
or like this:
```makefile
targets : prerequisites ; recipe
recipe
```
So:
- targets: the targets of this rule.
- prerequisites: could be other targets to call other rules before the recipe and they can define some local variables.
- recipe: an only-shell code area.

The main linux commands are delegated via the following commands:
```make
# build
.build-impl: .build-pre
	make -f nbproject/Makefile-${CONF}.mk SUBPROJECTS=${SUBPROJECTS} .build-conf

# clean
.clean-impl: .clean-pre
	make -f nbproject/Makefile-${CONF}.mk SUBPROJECTS=${SUBPROJECTS} .clean-conf

# clobber
.clobber-impl: .clobber-pre .depcheck-impl
	    make SUBPROJECTS=${SUBPROJECTS} CONF=default clean

# all
.all-impl: .all-pre .depcheck-impl
	    make SUBPROJECTS=${SUBPROJECTS} CONF=default build
```
Here, the prerequisites are used to run other targets and the recipes are used to do the shell job, where `make -f` runs another make script that enboxes the linux commands from the user inside the `nbproject` dir, but you could modify its variables to change the behavior of the netbeans project.

For example, here is the `nbproject/Makefile-default.mk` that builds the project:

<details>
<summary>nbproject/Makefile-default.mk</summary>
<br>

```makefile
#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=HelloWorld.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/HelloWorld.o
POSSIBLE_DEPFILES=${OBJECTDIR}/HelloWorld.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/HelloWorld.o

# Source Files
SOURCEFILES=HelloWorld.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega32"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega32
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/6a51431beb392e907f6b3ccd1f3622fa2e4d3cce .generated_files/flags/default/a9edf5460440a7b1aab639ef0e55e0f479cf2a8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/HelloWorld.o.d" -MT "${OBJECTDIR}/HelloWorld.o.d" -MT ${OBJECTDIR}/HelloWorld.o  -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/14c3d94448c6be114e535380d72a58a479d6346a .generated_files/flags/default/a9edf5460440a7b1aab639ef0e55e0f479cf2a8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega32 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/HelloWorld.o.d" -MT "${OBJECTDIR}/HelloWorld.o.d" -MT ${OBJECTDIR}/HelloWorld.o  -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega32 ${PACK_COMMON_OPTIONS}  -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 

else
${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega32 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/HelloMPLab.X.${IMAGE_TYPE}.hex"

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
```

</details>

There are lots of details here, the variables for this file (eg: `${MP_CC}` and `${MP_CPP}`) are defined within the `Makefile-local-default.mk` file and points at the GCC and the G++ avr compiler.

The rest of the file defines how the native image (object files) will be made out of the GCC, in this case there are 2 options, either output a real `.hex` image if the `TYPE_IMAGE` isn't a `DEBUG_RUN` or output an image with `.elf` extension to be used within a debugger (or simulator).

To upload the code using MPLab.X IDE, you will need a PIC MCU based programmer, otherwise you need to inject an avrdude command to the `.build-post` suffix rule as follows:

- In the `Makefile-variables.mk` file, define the following varibales:
```makefile
# Variables for the avrdude .upload-impl
PROGRAMMER='usbasp'
CHIP_ALIAS='m32'
BAUD_RATE='9600'
PORT='/dev/ttyUSB0'
SCK-HZ='187500Hz'
```
- In the `Makefile-impl.mk` file, define a variable to call the avrdude with the variables defined at the `Makefile-variables.mk` file: 
```makefile
# Add the upload script here
AVRDUDE_UPLOAD=avrdude -c${PROGRAMMER} -p${CHIP_ALIAS} -b${BAUD_RATE} -P${PORT} -B${SCK-HZ} -U flash:w:${CND_BASEDIR}'/'${CND_ARTIFACT_PATH_default}
```
- In the `Makefile-impl.mk` file, define the following suffix rule with a `recipe` calling the avrdude command defined previously in `AVRDUDE_UPLOAD` variable:
```makefile
# code upload
.upload-impl:
        ${AVRDUDE_UPLOAD}
```
- In the main `Makefile`, make a call to the `.upload-impl` suffix rule in the `prerequisite` part of `.build-post` rule:
```makefile
.build-post: .build-impl .upload-impl
```
- Now running the `make all` will clean, build and upload the code to the chip !
- Here is the logs from MPLab.X IDE:
<details>
<summary>Clean, build and upload logs</summary>
<br>

```shell
CLEAN SUCCESSFUL (total time: 53ms)
make -f nbproject/Makefile-default.mk SUBPROJECTS= .build-conf
avrdude -c'usbasp' -p'm32' -b'9600' -P'/dev/ttyUSB0' -B'187500Hz' -U flash:w:`pwd`'/'dist/default/production/HelloMPLab.X.production.hex
make[1]: warning: jobserver unavailable: using -j1.  Add '+' to parent make rule.
make[1]: Entering directory '/home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X'
make  -f nbproject/Makefile-default.mk dist/default/production/HelloMPLab.X.production.hex
make[2]: Entering directory '/home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X'
"/home/twisted/GradleProjects/AVR-Sandbox/avr8-gnu-toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-gcc"   -mmcu=atmega32 -I "/opt/microchip/mplabx/v6.00/packs/Microchip/ATmega_DFP/2.4.131/include" -B "/opt/microchip/mplabx/v6.00/packs/Microchip/ATmega_DFP/2.4.131/gcc/dev/atmega32"  -x c -c -D__ATmega32__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "build/default/production/HelloWorld.o.d" -MT "build/default/production/HelloWorld.o.d" -MT build/default/production/HelloWorld.o  -o build/default/production/HelloWorld.o HelloWorld.c  -DXPRJ_default=default   
"/home/twisted/GradleProjects/AVR-Sandbox/avr8-gnu-toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-gcc"  -mmcu=atmega32 -B "/opt/microchip/mplabx/v6.00/packs/Microchip/ATmega_DFP/2.4.131/gcc/dev/atmega32"  -D__ATmega32__  -Wl,-Map="dist/default/production/HelloMPLab.X.production.map"    -o dist/default/production/HelloMPLab.X.production.elf build/default/production/HelloWorld.o      -DXPRJ_default=default    -Wl,--defsym=__MPLAB_BUILD=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
"/home/twisted/GradleProjects/AVR-Sandbox/avr8-gnu-toolchain/avr8-gnu-toolchain-linux_x86_64/bin"/avr-objcopy -O ihex "dist/default/production/HelloMPLab.X.production.elf" "dist/default/production/HelloMPLab.X.production.hex"
make[2]: Leaving directory '/home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X'
make[1]: Leaving directory '/home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X'

avrdude: set SCK frequency to 187500 Hz
avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e9502 (probably m32)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: set SCK frequency to 187500 Hz
avrdude: reading input file "/home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex"
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex auto detected as Intel Hex
avrdude: writing flash (118 bytes):

Writing | ################################################## | 100% 0.07s

avrdude: 118 bytes of flash written
avrdude: verifying flash memory against /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex:
avrdude: load data flash data from input file /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex:
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex auto detected as Intel Hex
avrdude: input file /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex contains 118 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.04s

avrdude: verifying ...
avrdude: 118 bytes of flash verified

avrdude done.  Thank you.


BUILD SUCCESSFUL (total time: 811ms)
Loading code from /home/twisted/GradleProjects/AVR-Sandbox/HelloMPLab.X/dist/default/production/HelloMPLab.X.production.hex...
Program loaded with pack,ATmega_DFP,2.4.131,Microchip
Loading completed
```

</details>
