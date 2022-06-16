/**
 * @file AvrDataTypes.c
 * @author pavl_g
 * @brief An example demonstrates the different available integer types, their usages and bitwise operations.
 * @version 0.1
 * @date 2022-06-15
 * @copyright Copyright (c) Scrappers 2022
 * @note for more refer to the associated docs and attachments on the folder ./AvrDataTypes/Resources
 */
#include<avr/io.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

void usart_init(void) {
	UCSR0B = 0b00001000; // TXEN_BIT = 1, enables the transmitter buffer register.
	UCSR0C = 0b10000110; // enables the UCSZ0, UCSZ1 and URSEL
	UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

void usart_send(uint8_t character) {
	while (! (UCSR0A & (1 << UDRE0)));
	UDR0 = character;
}

/**
 * @brief Prints integer data in new line to the serial.
 * 
 * @param data 8-bit integer data, with max 256 (in dec) or 0b11111111 (in bin)
 */
void println(uint8_t data) {
    char strBuffer[256];
    // convert input to string
    itoa(data, strBuffer, 2);
    strcat(strBuffer, "\n");
    int i = 0;
    while (i < strlen(strBuffer)) {
        usart_send(strBuffer[i++]);
    }
}

int main(void) {
    usart_init();

    // 1) the unsigned 8 bit int: used for registers and bit data
    // volatile: means marked and present on the volatile memory, which is true in case of registers data
    volatile uint8_t PORTX = 0b00000000;
    volatile uint8_t PORTY = 0b11001100;
    
    println(PORTY);
    // const: means marked as a constant value with respect to its domain.
    // first pin
    const uint8_t PIN_0 = 1 << PORTX;
    // second pin
    const uint8_t PIN_1 = 1 << PIN_0;
    // third pin, another way to represent it, using indices
    const uint8_t PIN_2 = 3 << PORTX;
    // the unsigned 8 bit int is the same as the unsigned char, so its the same as 
    volatile unsigned char portB = PORTB;

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
    println(combined_reg);
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
    println(OR_AB);
    const uint8_t AND_AB = inputA & inputB; /* 0b00000000, usage: compares the binary commands and find if they both are equal to HIGH (1) */
    println(AND_AB);
    const uint8_t XOR_AB = inputA ^ inputB; /* 0b11000011, usage: compares the binary commands and find if they are both equal (Q = 0) or not (Q = 1)*/
    println(XOR_AB);
    const uint8_t NAND_AB = ~AND_AB; /* 0b11111111, usage: */
    println(NAND_AB);
    const uint8_t NOR_AB = ~OR_AB; /* 0b00111100, usage: finds all the non-involved bits in the OR */
    println(NOR_AB);
    const uint8_t NXOR_AB = ~XOR_AB; /* 0b00111100, usage: tests whether the 2 inputs are the same (Q = 1) or not (Q = 0).*/
    println(NXOR_AB);

    while(1); // block the program !

    return 0;
}


