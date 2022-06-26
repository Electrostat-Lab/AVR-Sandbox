## Avr-Data-Types

An example demonstrates the available data types in avr-gnu lib.

Topics covered: 
- Different integer data types (uint8_t, uint16_t, uint32_t) and their equivalent compound types.
- Converting integers to strings.
- UART printing strings and integers.
- Bitwise operations.
- Principal and combinatoric logic gates (and their equivalent gates).
- Allocating and deallocating pointers (buffers) before use.
- Some strings utility functions.

----------------------------------------------------------------------------------------------------------

1) Different integer datatypes, defined on `stdint.h`: 

| `Data type` | `Equivalent type` | `Size` | `MIN_VALUE` | `MAX_VALUE` |
|-------------|-------------|-------------|-------------|-------------|
| uint8_t | unsigned char | 8-bit | 0 | 256 (in decimal), 0b(11111111) (in binary), 0x(FF) (in hex) |
| uint16_t | unsigned int | 16-bit | 0 | 512 (in dec), 0b(11111111)(11111111) (in bin), 0x(FF)(FF) (in hex) |
| uint32_t | unsigned long int | 32-bit | 0 | 1024 (in dec), 0b(11111111)(11111111)(11111111)(11111111) (in bin), 0x(FF)(FF)(FF)(FF) (in hex)  | 

2) Converting integers to strings: 
- Use the function `itoa(int val, char* buffer, int radix)` offered by `<stdlib.h>` as it converts the integer value from `val` into an ASCII representation that will be stored under `s`, the 
buffer size depends on the radix, if it's 10 (decimal) then the buffer size = `sizeof(uint8_t) + 1`; where the additional charachter is the string termination char `\0` or `NULL`, if the radix is 2 (binary) then the buffer size = `8 * sizeof(uint8_t) + 1`; where 8 is the number of bits in an integer to be converted to string in the form of binary digits.
- Example: 
```c
const uint8_t SIZE_OF_BINARY_INTEGER_STR = 8 * sizeof(uint8_t) + 1; // 8 -> number of bits to be converted to chars, 1 -> string terminator constant '\0'
char* strBuffer = (char*) calloc(1, SIZE_OF_BINARY_INTEGER_STR);
// convert input to string
const char* output = itoa(data, strBuffer, radix); // now : output = strBuffer
```

3) UART printing strings and integers:

- Printing strings in the same line: 
```c
#include<string.h>
...
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
```
- Printing strings in a new line on the serial Tx: (just add `sprint(NEW_LINE_CARRIAGE_R)`)
```c
#include<string.h>

#define NEW_LINE_CARRIAGE_R (char*)"\n\r"
...
/**
 * @brief Prints string data in new line to the serial.
 * 
 * @param data char array string
 */
void sprintln(char* data) {
    sprint(data);
	sprint(NEW_LINE_CARRIAGE_R);
}
```
- Printing integers in the same line: 
```c
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
...
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
```
- Printing integers in a new line: (just add `sprint(NEW_LINE_CARRIAGE_R)`)
```c
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
```

4) Bitwise operations:
s
- Logical operations:

| `Gate` | `Notation` | `Maths Notation` | `Usage` | `Boolean Expression` |
|-------------|-------------|-------------|-------------|-------------|
| AND | `(...&...)` | `Q = A . B` | Mulitplying 2 binary digits | `Q = A & B` |
| OR | (...`|`...) | `Q = A + B` | Adding up 2 binary digits | Q = A `|` B |
| NOT | `~(...)` | `Q = !A` | Flipping the binary bits | `Q = ~A` |
| XOR (Ex-OR) | (...`^`...) | `Q = (!(A) . B)` | `(A . ~B)` | Checking if 2 binary digits' bits aren't the same | (~(A) `&` B) `|` (A `&` ~B) |
| N-XOR (NOT-Ex-OR) | ~(...`^`...) | Q = !((!(A) . B) `|` (A . ~B)) | Checking if 2 binary digits' bits are the same | ~((~(A) `&` B) `|` (A `&` ~B)) | 
| N-AND | ~(...`&`...) |  `Q = !(A . B)` | State and circuit control when 2 states are true, the result is false and when the two states are false or one of them is false, the result is true | `Q = ~(A & B)` |
| N-OR | ~(...`|`...) | `Q = !(A + B)` | - | Q = ~(A `|` B)

- Shifting operations

| `Operator` | `Notation` | `Name` | `Usage` | `Equivalent maths equation` | `Example` |
|-------------|-------------|-------------|-------------|-------------|-------------|
| `<<` | `BINARY_NUMBER << NUM_OF_SHIFTS` | Left shift | Left shifting bits on (BINARY_NUMBER) by a number of times (NUM_OF_SHIFTS) | `BINARY_NUMBER * pow(2, NUM_OF_SHIFTS)` | `(0b00001110 << 3) is the same as (((0b00001110 << 1) << 1) << 1)` | 
| `>>` | `BINARY_NUMBER >> NUM_OF_SHIFTS` | Right shift | Right shifting bits on (BINARY_NUMBER) by a number of times (NUM_OF_SHIFTS) | `BINARY_NUMBER * pow(2, -NUM_OF_SHIFTS)` | `(0b00111000 >> 3) is the same as (((0b00111000 >> 1) >> 1) >> 1)` | 

- Addition
- Subtraction


