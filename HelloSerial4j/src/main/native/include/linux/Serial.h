#ifndef SERIAL
#define SERIAL

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

#define BUFFER_SIZE (1)
#define DEVICES_DIR ((const char*) "/dev/")

#define ERR_INVALID_PORT (-2)
#define ERR_INVALID_DIR (-3)
#define ERR_NO_RESULT (0)
#define OPERATION_SUCCEEDED (1)

#define DEFAULT_FLAG (O_RDWR | O_NONBLOCK | O_NOCTTY)

namespace Terminal {

    struct TerminalControl {

        static inline char* concatIntoDevice(char* src, const char* file) {
            strcat(src, DEVICES_DIR);
            strcat(src, file);
            return src;
        }

        /**
         * @brief Tests whether the PATH specified is a real serial port.
         * 
         * @param path the path to specify if its a serial port.
         * @return int 1 if FD is a valid descriptor, 0 otherwise.
         */
        static inline int isSerialPort(char* path) {
            int fdp = open(path, DEFAULT_FLAG);
            int state = isatty(fdp);
            close(fdp);
            return state;
        }

        /** terminal attrs */
        termios tty;
        int portFileDescriptor;
        int baudRate;

        /** Serial Ports buffer */
        DynamicBuffer serialPorts;

        /** R/W buffers */
        int writeBuffer[BUFFER_SIZE];
        int readBuffer[BUFFER_SIZE];
        
        int fetchSerialPorts();

        int& openPort(const char* port);

        int initTermios();

        /**
         * @brief Get the Serial Ports in a string array format.
         * 
         * @return const char** the serial ports in a string array format.
         */
        const char** getSerialPorts() {
            return (const char**) serialPorts.getBuffer();
        }

        /**
         * @brief Sets the Baud Rate object for the terminal io.
         * 
         * @param baudRate 
         * @return int 
         */
        int setBaudRate(int baudRate);

        speed_t getBaudRate();

        ssize_t writeData();

        ssize_t readData();

        int closePort();

        int& getPortFileDescriptor();

        int& getErrno();

    };
}


#endif