# define common variables here
SHELL = '/bin/bash'

# CHIP Charachteristics
CHIP_ALIAS = m328p
PROGRAMMER = arduino
BAUD_RATE  = '57600'
PORT       = '/dev/ttyUSB0'
CHIP       = 'atmega328p'
AVR_DUDE   = avrdude -c ${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS}

# Map shell commands to some makefile set of rules

compile: 
	source 'shell-build/compile.sh'

upload: 
	source 'shell-build/upload.sh'

terminal-mode: 
	sudo ${AVR_DUDE} -t

build: compile upload
