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

avr_examples_dir="${project%/*}"

hello_native_libs="${avr_examples_dir%/*}"
# cut the working directory from its end by a one '/' delimiter again
rootProject="${hello_native_libs%/*}"
# pass the value of the dire

clibName=('libuart')
# AVR-DUDE properties
CHIP='atmega328p'

# Common Variables contain colors
source ${rootProject}'/CommonVariables.sh'
# provide avr home
AVR_HOME=${rootProject}'/avr8-gnu-toolchain-linux_x86_64'
output=${project}'/output/'${clibName}
