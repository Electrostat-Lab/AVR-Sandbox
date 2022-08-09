#!/bin/sh
##
# Shell script to read from serial port with
# an operating baud rate.
#
# @param $1 ---> superuser password.
# @param $2 ---> serial port description.
# @param $3 ---> serial port operating baud rate.
#
# @author pavl_g.
##

##
# Initializes a port with a baud rate.
#
# @param $1 ---> superuser password.
# @param $2 ---> port description.
# @param $3 ---> port operating baud rate.
##
initPort() {
    password=$1
    port=$2
    baudRate=$3

    echo "${password}" | sudo -S stty -F "${port}" "${baudRate}"
}

password=$1
port=$2
baudRate=$3

initPort "${password}" "${port}" "${baudRate}"
