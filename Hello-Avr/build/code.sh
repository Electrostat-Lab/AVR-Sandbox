source variables.sh

output=${project}'/output/'${clibName}

function compile() {
	# attrs : dir to compile & sharedLib name
        nativeSources=`find ${project}'/main' -name '*.c' -o -name '*.cxx' -o -name '*.cpp' -o -name '*.h' -o -name '*.c++'`

	sudo ${AVR_HOME}'/bin/avr-g++' \
	-mmcu=${CHIP} ${nativeSources} \
	-I${AVR_HOME}'/avr/include'	\
	-o ${output}
	return $?
}

function convertToHex() {
  	 ${AVR_HOME}'/bin/avr-objcopy' -O ihex ${output} ${output}'.hex'
	 return $?
}

function upload() {
	sudo avrdude -c ${PROGRAMMER} -b${BAUD_RATE} -P${PORT} -p${CHIP_ALIAS} -F -U flash:w:${output}'.hex'
	return $?
}
