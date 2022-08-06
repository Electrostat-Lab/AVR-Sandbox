echo 'root12345678' | sudo -S stty -F '/dev/ttyUSB0' '57600'
echo 'root12345678' | sudo -S chmod o+rw /dev/ttyUSB0

printf %s "0" > '/dev/ttyUSB0'


