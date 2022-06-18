#ifndef REG
#define REG

#define __STDC_CONSTANT_MACROS

#include<avr/io.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#define HIGH UINT8_C(0b01)
#define LOW UINT8_C(0b00)

/**
 * @brief Converts a register to an array logic of bits using utility methods.
 */
namespace Register {

    const static uint8_t PORT[] = {0, 1, 2, 3, 4, 5, 6, 7};

    struct Register8 {

        /**
         * @brief Gets the Length of array [PORT*] from its size.
         * 
         * @param PORT[] change the PORT array and re-run this to get the length of the new PORT array
         * @return size_t 
         */
        size_t getLength();

        /**
         * @brief Digitally writes a [STATE] to a [PIN] in a particular [PORT].
         * 
         * @param PORT the register
         * @param PIN the pin
         * @param STATE the STATE, either [Regiter::HIGH] or [Register::LOW]
         */
        void digitalWrite(volatile uint8_t& PORT, const uint8_t& PIN, const uint8_t& STATE);

        /**
         * @brief Digitally reads a [PIN] in a [PORT].
         * 
         * @param PORT the register
         * @param PIN the pin to read from
         * @return const uint8_t a new unsigned char decimal number representing the current state or zero
         */
        const uint8_t digitalRead(volatile uint8_t& PORT, const uint8_t& PIN);
    };
};
#endif
