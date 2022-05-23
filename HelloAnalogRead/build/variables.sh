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
