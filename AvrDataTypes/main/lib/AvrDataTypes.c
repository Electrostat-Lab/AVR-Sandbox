/**
 * @file AvrDataTypes.c
 * @author pavl_g
 * @brief An example demonstrates the different available integer types, their usages and bitwise operations.
 * @version 0.1
 * @date 2022-06-15
 * @copyright Copyright (c) Scrappers 2022
 * @note for more refer to the associated docs and attachments on the folder ./AvrDataTypes/resources
 */
#define __STDC_CONSTANT_MACROS

#include<avr/io.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// user-defined libs
#include<Register.h>
#include<SerialCounter.h>

#define NEW_LINE_CARRIAGE_R (char*)"\n\r"
#define DEC_RADIX (uint8_t) 10
#define CHAR_OF_DEC (size_t) (1 * sizeof(uint8_t) + 1) /* For example: 155 is the same as saying [const char str[] = {'155', NULL};] or [char str[] = {'155', '\0'};]*/

#define BIN_RADIX (uint8_t) 2
#define CHAR_OF_BIN (size_t) (8 * sizeof(uint8_t) + 1) /* For example: 0b11110000 is the same as saying [const char str[] = {'1', '1' ,'1', '1', '0', '0', '0', '0', '\0'};], 
																	   i.e. one character for each bit plus one for the string terminator '\0' which is (NULL). */


// preprocessor functions/methods declarations
void usart_init(void);
void usart_send(uint8_t);
void print(uint8_t, uint8_t);
void println(uint8_t, uint8_t);
void sprint(char*);
void sprintln(char*);
char* substring(char*, uint8_t, uint8_t);
int main(void);

/**
 * @brief Initializes the UART protocol.
 */
void usart_init(void) {
    UCSR0B = 0b00001000; // TXEN_BIT = 1, enables the transmitter buffer register.
    UCSR0C = 0b10000110; // enables the UCSZ0, UCSZ1 and URSEL
    UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

/**
 * @brief Sends a character to UART UDR0 register.
 * 
 * @param character a char to send (unsigned char) of 8-bits
 */
void usart_send(uint8_t character) {
    while (! (UCSR0A & (1 << UDRE0)));
    UDR0 = character;
}

/**
 * @brief Prints integer data to the serial.
 * 
 * @param data 8-bit integer data, with max 256 (in dec) or 0b11111111 (in bin)
 * @param radix the data number system base
 */
void print(uint8_t data, uint8_t radix) {
    char* strBuffer;
    if (radix == BIN_RADIX) {
	strBuffer =(char*) calloc(1, CHAR_OF_BIN);
    } else if (radix == DEC_RADIX) {
	strBuffer =(char*) calloc(1, CHAR_OF_DEC);
    } else {
	return;
    }
    // convert input to string
    itoa(data, strBuffer, radix);
    int i = 0;
    while (i < strlen(strBuffer)) {
        usart_send(strBuffer[i++]);
    }
    free(strBuffer);
}

/**
 * @brief Prints integer data in new line to the serial.
 * 
 * @param data 8-bit integer data, with max 256 (in dec) or 0b11111111 (in bin)
 * @param radix the data number system base
 */
void println(uint8_t data, uint8_t radix) {
    print(data, radix);
    sprint(NEW_LINE_CARRIAGE_R);
}

/**
 * @brief Prints string data to the serial.
 * 
 * @param data char array string
 */
void sprint(char* data) {
    int i = 0;
    while (i < strlen(data)) {
        usart_send(data[i++]);
    }
}

/**
 * @brief Prints string data in new line to the serial.
 * 
 * @param data char array string
 */
void sprintln(char* data) {
    sprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}

/**
 * @brief Cuts a string data from [start] to [end] indices and print a new buffer.
 * 
 * @param str the string to cut
 * @param start the start index
 * @param end the end index
 * @return char* a new buffer
 */
char* substring(char* str, uint8_t start, uint8_t end) {
    char* buffer = (char*) calloc(1, sizeof(str));
    int i = 0;
    int bufferIndex = 0;
    while (i < strlen(str)) {
        if (i < start) {
            i+=1;
            continue;
        }
        if (i > end) {
            break;
        }
        buffer[bufferIndex++] = str[i++];
    }
    return buffer;
}

/**
 * @brief A structure used to test pointers and pointers operations.
 */
struct Leds {
    int* rows;
    int* columns;
} LEDS;

int main(void) {
    
    usart_init();

    // 1) the unsigned 8 bit int: used for registers and bit data
    // volatile: means marked and present on the volatile memory, which is true in case of registers data
    volatile uint8_t PORTX = 0b00000000;
    volatile uint8_t PORTY = 0b11001100;

    sprintln((char*) "Imaginery PORTY:");
    println(PORTY, 2);
    // const: means marked as a constant value with respect to its domain.
    // first pin
    const uint8_t PIN_0 = 1 << PORTX;
    // second pin
    const uint8_t PIN_1 = 1 << PIN_0;
    // third pin, another way to represent it, using indices
    const uint8_t PIN_2 = 3 << PORTX;
    // the unsigned 8 bit int is the same as the unsigned char, so its the same as 
    volatile unsigned char portB = PORTB;
    
    sprintln((char*) "PORTB before setting LED PIN5:");
    println(PORTB, 2);

    PORTB = 1 << PB5; // is the same as (0b0000001 << 5) and 0b00100000

    sprintln((char*) "PORTB after setting LED PIN5:");
    println(PORTB, 2); // 0b00100000

    Register::Register8* reg8 = (Register::Register8*) calloc(1, sizeof(Register::Register8));
    
    // toggle all bits on register uint PORTB to LOW
    for (int i = 0; i < reg8->getLength(); i++) {
        reg8->digitalWrite(PORTB, Register::PORT[i], LOW);
    }
    sprintln((char*) "PORTB turned all LEDs to LOW:");
    println(PORTB, 2);


    sprintln((char*) "PORTC initially:");
    println(PORTC, 2); // 0

    // toggle all bits on register uint PORTC to HIGH
    for (int i = 0; i < reg8->getLength(); i++) {
        reg8->digitalWrite(PORTC, Register::PORT[i], HIGH);
    }

    sprintln((char*) "PORTC turned all LEDs to HIGH:");
    println(PORTC, 2);

    sprintln((char*) "PORTB PB5: ");
    // read PIN5 LED on PORTB
    println(reg8->digitalRead(PORTB, PB5), 2);


    // 2) the unsigned 16 bit int: used for 2 parts registers (2 8-bits registers), for example: some
    // adc and timer registers
    // it's equivalent to unsigned int 
    volatile uint16_t reg_16_bit = TCNT0;
    
    // 3) the unsiged 32 and 64 bit integers: used to combine different values of registers together 
    // by left shifting them, could be also used to store arbitrary values for screens and large
    // number of charachter values
    // it's equivalent to unsigned long int
    volatile char position = 0;
    volatile uint32_t combined_reg = (++position) << PORTX;
    combined_reg = (++position) << PORTY;
    println(combined_reg, 2);
    // now we have a 16-bit filled space, there is still another free 16-bits !

    // 4) the signed int data types are for anticipated negative values.

    // 5) Bitwise operators: Shifting bits and logical operators.
    // left shifting: BINARY << SHIFT_TIMES = BINARY * Math.pow(2, SHIFT_TIMES)
    uint8_t x = (1 << 0b00000001) /*0b00000010*/ | (1/*0b0001*/ << 0b00000011/*3*/) /*0b00001000*/; /*0b01010*/ /* 10 */
    uint8_t y = (0b00000001 << 1) /*0b00000010*/ | (0b00000011 << 1)                /*0b00000110*/; /*0b00000110*/ /* 6 */
    
    // right shifting: BINARY >> SHIFT_TIMES  = BINARY * Math.pow(2, -SHIFT_TIMES)
    uint8_t testRightShifting = (0b00001000 >> 3); /* 0b0001 = 1*/
    uint8_t testLeftShifting = (0b00001000 << 3); /* 0b0001000000 = 64*/

    // TIPs to minimize errors: the BINARY value should be your lvalue.

    // 6) Bitwise logical operations:
    
    /* -- Principal logical gates -- */
    // (|): Bitwise logical OR, designated by the (+) sign in boolean algebra.
    // (&): Bitwise logical AND, designated by the (.) sign in boolean algebra.
    // (~): Bitwise logical NOT, designated by the dash or the bar (A`) sign in boolean algebra.

    /* -- Combinatoric logic gates -- */
    // (^): Bitwise exclusive OR (XOR), produces Q = 1, if only and only one of the inputs is 1, otherwise produces Q = 0
    // Note: Q = A ^ B is the same as Q = (~(A) & B) | (A & ~B)
    // ~(&): Bitwise logical NAND
    // ~(|): Bitwise logical NOR
    // ~(^): Bitwise logical NXOR, produces Q = 1, if only and only the two inputs are the same (whether they are zero or one), otherwise produces Q = 0 
    // Note: Q = ~(A ^ B) is the same as Q = ~((~(A) & B) | (A & ~B))
    uint8_t inputA = 0b00000011;
    uint8_t inputB = 0b11000000;
    const uint8_t OR_AB = inputA | inputB; /* 0b11000011, usage: concatenates the binary commands into a single command */ 
    println(OR_AB, 2);
    const uint8_t AND_AB = inputA & inputB; /* 0b00000000, usage: compares the binary commands and find if they both are equal to HIGH (1) */
    println(AND_AB, 2);
    const uint8_t XOR_AB = inputA ^ inputB; /* 0b11000011, usage: compares the binary commands and find if they are both equal (Q = 0) or not (Q = 1)*/
    println(XOR_AB, 2);
    const uint8_t NAND_AB = ~AND_AB; /* 0b11111111, usage: */
    println(NAND_AB, 2);
    const uint8_t NOR_AB = ~OR_AB; /* 0b00111100, usage: finds all the non-involved bits in the OR */
    println(NOR_AB, 2);
    const uint8_t NXOR_AB = ~XOR_AB; /* 0b00111100, usage: tests whether the 2 inputs are the same (Q = 1) or not (Q = 0).*/
    println(NXOR_AB, 2);
	
    // 7) Binary addition/subtraction
    
    // addition
    const uint8_t BINARY_1 = 0b00000010; // 2
    const uint8_t BINARY_2 = 0b00000011; // 3
    const uint8_t SUM = BINARY_1 + BINARY_2; /* 0b00000010 + 0b00000011 = 0b00000101 (5), (0 + 1 = 1), (1 + 1 = 0 and carry 1 to the MSB -- most significant bit) */
    sprintln((char*) "Test Binary Addition:");
    println(SUM, 2);
    
    // subtraction, DIFF = SUM - BINARY_2 = 0b00000101 - 0b00000011 = 0b00000101 + (0b11111100 + 0b00000001) = 0b00000101 + 0b11111101 = 0b00000010 (2 in Decimal)
   
    // Steps: 
    // 1- Finds the 1s complement of the subtrahend number: 
    const uint8_t onesComplement = ~BINARY_2;
    // 2- Finds the 2s complement by adding (0b01) to the ones complement:
    const uint8_t twosComplement = onesComplement + 0b01;
    // 3- Add the 2s complement to the minuend (1st binary number): 
    const uint8_t DIFF = SUM + twosComplement;
    sprintln((char*) "Test Binary Subtraction:");
    println(DIFF, 2);

    // 8) Strings: strings are represented in the form of character arrays or pointer
    char* name = (char*) calloc(1, sizeof(char*));
    char* id = (char*) calloc(1, sizeof(char*));

    name = (char*) "Jack";
    sprintln(name);

    id = (char*) "125";
    sprintln(id);

    // concat strings
    const char* lastName = " Richard";
    
    sprintln((char*) "Test String concat:");
    strcat(name, lastName);
    sprintln(name);
    
    // release the resources
    free(name);
    free(id);
    free((void*) lastName);

    // compare 2 strings 
    sprintln((char*) "Test String compare:");
    uint8_t result = strcmp(name, id);
    println(result, 10);
	
    sprintln((char*) "Mem size V.S. String len:");
    // find the length (number of chars) of a string
    uint8_t len = strlen(name);
    println(len, 10);

    // find the size of the string in bytes
    uint8_t memorySize = sizeof(name);
    println(memorySize, 10);

    // ctype: charachter type utilities
    sprintln((char*) "Charachter operations:");
    println(isupper('C'), 10);
    println(islower('C'), 10);
    println(tolower('C'), 10);
    println(toascii('C'), 10);
    println(isblank(' '), 10);


    // 8) Test pointers and pointers operations

    sprintln((char*) "Pointer operations: ");
    // pointer points to the first member (0)
    println(*(LEDS.rows), 10);
    LEDS.rows[0] = 1;
    LEDS.rows[1] = 3;
    LEDS.rows[2] = 4;
    // pointer points to the first member (1)
    println(*(LEDS.rows), 10);
    // prefix increment operations on pointers --> gives us the pointer to the 2nd member (3)
    println(*(++LEDS.rows), 10);

    // test xmas 
    sprintln((char*) "Test Xmas LEDs started, connect PORTB pins to LEDs and see the magic:");
    SerialCounter::Counter* counter = (SerialCounter::Counter*) calloc(1, sizeof(SerialCounter::Counter*));
    counter->start(PORTB);

    while(1); // block the program !

    return 0;
}
