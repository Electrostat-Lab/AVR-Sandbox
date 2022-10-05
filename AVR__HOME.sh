# store the value of the working directory
tmp=`pwd`
# get back to the root project to find the toolchain
cd ..
cd ..
project_root=`pwd`
AVR_HOME=$project_root'/avr8-gnu-toolchain-linux_x86_64'
# get back to the working directory
cd $tmp
