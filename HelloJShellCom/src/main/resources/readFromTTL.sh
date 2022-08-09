#!/bin/sh
##
# Shell script to read from serial port with
# an operating baud rate.
#
# @param $1 ---> serial port description.
# @param $2 ---> serial port operating baud rate.
#
# @author pavl_g.
##


##
# Reads a port with a baud rate.
#
# @param $1 ---> port description.
# @param $2 ---> baud rate.
##
readPort() {
    port=$1
    baudRate=$2

    INPUT=""
      while true
      do
          read -r INPUT < "$port"

          if [ "$INPUT" != "" ]; then
              echo "$INPUT"
          fi

      done
}

port=$1
baudRate=$2

readPort "${port}" "${baudRate}"