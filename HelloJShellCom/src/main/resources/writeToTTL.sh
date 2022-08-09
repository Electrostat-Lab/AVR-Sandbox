#!/bin/sh
##
# Shell script to write to serial port with
# an operating baud rate.
#
# @param $1 ---> superuser password.
# @param $2 ---> serial port description.
# @param $3 ---> data to send to TTL.
#
# @author pavl_g.
##

##
# Sets the RW (o+rw) permissions for the port.
#
# @param $1 ---> superuser password.
# @param $2 ---> port description.
##
setRWPermissions() {
    password=$1
    port=$2

    echo "${password}" | sudo -S chmod o+rw "${port}"
}

##
# Writes data to the port.
#
# @param $1 ---> port description.
# @param $2 ---> data to write in string format.
##
write() {
    port=$1
    data=$2

    printf %s "${data}" > "${port}"
}

password=$1
port=$2
data=$3

setRWPermissions "${password}" "${port}"
write "${port}" "${data}"
