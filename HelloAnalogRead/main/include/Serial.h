/**
 * @file Serial.h
 * @author pavl_g.
 * @brief Controls the UART IO Protocol which involves send and receiving bits.
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SERIAL_UART
#define SERIAL_UART 1

#include<avr/io.h>
#include<string.h>
#include<stdlib.h>

#define BAUD_RATE_9600 ((const uint8_t) 0x67) 
#define BAUD_RATE_57600 ((const uint8_t) 0x10)

/**
 * @brief Defines a constant for the carriage return combined with the new line in a single value.
 */
#define NEW_LINE_CARRIAGE_R (char*)"\n\r"

/**
 * @brief Defines a constant for the decimal radix base to print the number in decimal case.
 */
#define DEC_RADIX (const uint8_t) 10

/**
 * @brief Defines a constant for the binary radix base to print the numbner in binary case.
 */
#define BIN_RADIX (const uint8_t) 2

/**
 * @brief Allocates an expandable string buffer for small/medium/large integers and clears the buffer to zero.
 * 
 * @example For decimal base 10: 155 is the same as saying [const char str[] = {'155', NULL};] or [char str[] = {'155', '\0'};].
 * @example For binary base 2: 0b11110000 is the same as saying [const char str[] = {'1', '1' ,'1', '1', '0', '0', '0', '0', '\0'};],
 * i.e. one character for each bit plus one for the string terminator '\0' which is (NULL).     
 */
#define allocateStringBuffer() ((char*) calloc(1, sizeof(char*))) 
 
/**
 * @brief Encloses the UART control code.
 */
namespace Serial {
    /**
     * @brief Operates, controls, read/write to UART serial port.
     */
    struct UART {

        /**
         * @brief Allocates a new UART pointer.
         * 
         * @return UART* a new pointer reference.
         */
        static UART* getInstance() {
            return (Serial::UART*) calloc(1, sizeof(Serial::UART*));
        }

        /**
         * @brief Starts the UART Protocol by setting up the control status registers and the baud rate register.
         * it operates the UART as Tx and Rx.
         * 
         * @param BAUD_RATE_VAL the code for the baud rate.
         */
        void startProtocol(const uint8_t& BAUD_RATE_VAL);

        /**
         * @brief Stops the UART protocol by setting [UCSRB] to zero.
         */
        void stopProtocol();

        /**
         * @brief Reads the [UDR0] Data register in ASCII as default.
         * 
         * @return uint8_t an 8-bit integer read from the UDR0, the output is in ascii.
         */
        uint8_t readASCII();

        /**
         * @brief Reads the [UDR0] Data register in Integers after converting from ASCII by subtracting the result from '0' aka [48].
         * 
         * @return uint8_t 
         */
        uint8_t readInteger();

        /**
         * @brief Prints a charachter data to the serial stream.
         * 
         * @param data a char data of 8-bit size.
         */
        void cprint(char& data);

        /**
         * @brief Prints a charachter data to the serial stream in a new line.
         * 
         * @param data a char data of 8-bit size.
         */
        void cprintln(char& data);
        
        /**
         * @brief Prints a string (char array) buffer to the serial stream.
         * 
         * @param data the string buffer to print.
         */
        void sprint(char* data);

        /**
         * @brief Prints a string (char array) buffer to the serial stream in a new line with a carriage return [(\n\r)].
         * 
         * @param data the string buffer to print.
         */
        void sprintln(char* data);

        /**
         * @brief Prints an integer data of max 64-bits with a base radix (2 for binary print or 10 for decimal print).
         * 
         * @param data the integer to print.
         * @param base the base, either 2 for binary print ()
         */
        void print(const int64_t& data, const uint8_t& base);
        
        /**
         * @brief Prints an integer data of max 64-bits with a base radix (2 for binary print or 10 for decimal print) 
         * in a new line with carriage return [(\n\r)].
         * 
         * @param data the integer to print.
         * @param base the base, either 2 for binary print (with max size = 64 * sizeof(uint8_t) + 1) or 10 for decimal print
         * (with max size = 1 * sizeof(int64_t) + 1).
         */
        void println(const int64_t& data, const uint8_t& base);
    };
}

#endif
