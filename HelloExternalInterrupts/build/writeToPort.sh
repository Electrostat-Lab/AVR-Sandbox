PORT='/dev/ttyUSB0'

writeData() {
    printf $1 > $PORT
}

writeData $1
