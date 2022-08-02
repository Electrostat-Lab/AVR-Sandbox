# define common variables here
SHELL = '/bin/bash'

# CHIP Charachteristics
CHIP_ALIAS = m328p
PROGRAMMER = arduino
BAUD_RATE  = '57600'
PORT       = '/dev/ttyUSB0'
CHIP       = 'atmega328p'
AVR_DUDE   = avrdude -c${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS}
fuse = ${SHELL ${1}}
# Map shell commands to some makefile set of rules

compile: 
	source 'shell-build/compile.sh'

upload: 
	source 'shell-build/upload.sh'

terminal-mode: 
	sudo ${AVR_DUDE} -F -t

##
# Test disable ESAVE bit by bringing the bit to one
# -V -> bypasses verfications
# -F -> force
##
setFuses: 
	sudo ${AVR_DUDE} -D -V -F -U'hfuse':w:0x08:m -U'lfuse':w:0x00:m -U'efuse':w:0x00:m

readFuses:
	sudo ${AVR_DUDE} -D -V -F -U'hfuse':r:-:i -U'lfuse':r:-:i -U'efuse':r:-:i

build: compile upload 




