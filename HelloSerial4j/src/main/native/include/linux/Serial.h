/**
 * @file Serial.h
 * @author pavl_g.
 * @brief Represents the serial port devices control and operation for POSIX systems.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright 
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef SERIAL
#define SERIAL "Serial4j-API"

#include<termios.h>
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<dirent.h>
#include<sys/stat.h>

#include<DynamicBuffer.h>
#include<SerialUtils.h>
#include<ErrnoUtils.h>
#include<Logger.h>

#define BUFFER_SIZE (1)
#define DEVICES_DIR ((const char*) "/dev/")

#define DEFAULT_FLAG (O_RDWR | O_NONBLOCK | O_NOCTTY)

namespace Terminal {

    struct TerminalControl {

        /** terminal attrs */
        termios tty;
        int portFileDescriptor;
        int baudRate;

        /** Param@0 = VTIME, Param@1 = VMIN */
        const cc_t POLLING_READ[2] = {0, 0};
        const cc_t BLOCKING_READ_ONE_CHAR[2] = {0, 1};
        const cc_t READ_WITH_TIMEOUT[2] = {1, 0};
        const cc_t READ_WITH_INTERBYTE_TIMEOUT[2] = {1, 1};

        /** Serial Ports buffer */
        struct DynamicBuffer serialPorts;

        /** R/W buffers */
        int writeBuffer[BUFFER_SIZE];
        int readBuffer[BUFFER_SIZE];
        
        /**
         * @brief Fetches serial port devices on "/dev/" into [serialPorts] buffer.
         * 
         * @return int (1) for success, (0) for no result.
         */
        int fetchSerialPorts();

        /**
         * @brief Opens a serial port device with a name.
         * 
         * @param port the path for the serial port device.
         * @return int* a memory reference for the port file descriptor.
         */
        int* openPort(const char* port);

        /**
         * @brief Initializes the default terminal with the following charachteristics: 
         * 
         * 
         * @return int (1) for success, (-1) for failure, (-2) for invalid port.
         */
        int initTermios();

        /**
         * @brief Sets the Read Configuration Mode using a ReadConfiguration with a
         * VMIN_VALUE for lesser bytes to read and VTIME_VALUE for the elapsed time to 
         * set if the ReadConfiguration mode provides a timeout.
         * 
         * @param readConfig the read configuration, either POLLING_READ, BLOCKING_READ_ONE_CHAR,
         * READ_WITH_TIMEOUT or READ_WITH_INTERBYTE_TIMEOUT.
         * @param VTIME_VALUE the value of the read timeout elapsed time, the timer starts 
         * with this value after read() is called.
         * @param VMIN_VALUE the value of the minimum number of bytes to read.
         * @return int (ERR_INVALID_PORT = -2) if port isn't available, (0) otherwise.
         */
        int setReadConfigurationMode(const cc_t* readConfig, const int VTIME_VALUE, const int VMIN_VALUE);

        /**
         * @brief Get the Serial Ports in a string array format.
         * 
         * @return const char** the serial ports in a string array format.
         */
        const char** getSerialPorts() {
            return (const char**) serialPorts.getBuffer();
        }

        /**
         * @brief Gets the Dynamic Buffer list containing the serial
         * devices.
         * 
         * @return struct DynamicBuffer* a buffer representing a list for serial ports.
         */
        struct DynamicBuffer* getDynamicBuffer() {
            return &serialPorts;
        }

        /**
         * @brief Sets the Baud Rate object for the terminal io.
         * 
         * @param baudRate the baud rate (bits/seconds).
         * @return int (1) for success, (-1) for failure, (-2) for invalid port.
         */
        int setBaudRate(int baudRate);

        /**
         * @brief Gets the Baud Rate object.
         * 
         * @return speed_t baud rate in integers.
         */
        speed_t getBaudRate();

        /**
         * @brief Writes data to the serial port device.
         * 
         * @return ssize_t the number of bytes written to the serial device.
         */
        ssize_t writeData();

        /**
         * @brief Reads data from the serial port device.
         * 
         * @return ssize_t the number of bytes read from the terminal.
         */
        ssize_t readData();

        /**
         * @brief Closes the serial port device.
         * 
         * @return int (1) for success, (-1) for failure, (-2) for invalid port.
         */
        int closePort();

        /**
         * @brief Gets the Port File Descriptor object.
         * 
         * @return int* a memory reference to the file descriptor of the serial port device.
         */
        int* getPortFileDescriptor();

        /**
         * @brief Gets the Errno object
         * 
         * @return int* a memory reference to the generated errno.
         */
        int* getErrno();

    };
}


#endif