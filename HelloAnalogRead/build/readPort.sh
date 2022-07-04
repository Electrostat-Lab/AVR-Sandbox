PORT='/dev/ttyUSB0'
BAUD_RATE='57600'

echo "\n"

echo "Started reading PORT [$PORT]\n"

adjustBaudRate() {
    stty -F $1 $2
}

readPort() {
    local INPUT=""
    while true
    do
        read INPUT < "$1"
        
        if [ "$INPUT" != "" ]; then
            echo "$INPUT"
        fi
        
    done
}

adjustBaudRate "$PORT" "$BAUD_RATE"

readPort "$PORT"