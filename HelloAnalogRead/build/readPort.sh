PORT='/dev/ttyUSB0'

echo "\n"

echo "Started reading PORT[$PORT]\n"

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

readPort "$PORT"