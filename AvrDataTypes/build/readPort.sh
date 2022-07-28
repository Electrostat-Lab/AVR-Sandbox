PORT='/dev/ttyUSB0'
BAUD_RATE='57600'

echo "\n"

echo "Started reading PORT [$PORT] to terminate hold [CTRL+A+D]\n"

adjustBaudRate() {
    stty -F $1 $2
}

readPort() {
    screen "$1" "$BAUD_RATE"
}

adjustBaudRate "$PORT" "$BAUD_RATE"

readPort "$PORT"
