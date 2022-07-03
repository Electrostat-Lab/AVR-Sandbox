/**
 * @file Serial.h
 * @author pavl_g
 * @brief Controls the UART IO Protocol which involves send and receiving bits
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

#define NEW_LINE_CARRIAGE_R (char*)"\n\r"
#define DEC_RADIX (uint8_t) 10
#define CHAR_OF_DEC (size_t) (1 * sizeof(uint8_t) + 1) /* For example: 155 is the same as saying [const char str[] = {'155', NULL};] or [char str[] = {'155', '\0'};]*/

#define BIN_RADIX (uint8_t) 2
#define CHAR_OF_BIN (size_t) (8 * sizeof(uint8_t) + 1)  // For example: 0b11110000 is the same as saying [const char str[] = {'1', '1' ,'1', '1', '0', '0', '0', '0', '\0'};],  
                                                        //  i.e. one character for each bit plus one for the string terminator '\0' which is (NULL). 
namespace Serial {
    struct UART {

        void startProtocol();
        void stopProtocol();

        uint8_t read();

        void cprint(char& data);
        void cprintln(char& data);

        void sprint(char* data);
        void sprintln(char* data);

        void print(const uint8_t& data, const uint8_t& base);
        void println(const uint8_t& data, const uint8_t& base);
    };
}

#endif
