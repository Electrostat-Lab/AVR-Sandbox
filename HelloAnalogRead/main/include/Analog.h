/**
 * @file Analog.h.
 * @author pavl_g.
 * @brief Operates and controls the ADC protocol through the ADC mulitplexers and status control registers.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ANALOG
#define ANALOG 1

#include<avr/io.h>
#include<string.h>
#include<stdlib.h>

/* define analog ADC pins based on the multiplexers codes */
#define ADC_MUX0 ((const uint8_t) 0x00)
#define ADC_MUX1 (ADC_MUX0 + 0x01)
#define ADC_MUX2 (ADC_MUX1 + 0x01)
#define ADC_MUX3 (ADC_MUX2 + 0x01)
#define ADC_MUX4 (ADC_MUX3 + 0x01)
#define ADC_MUX5 (ADC_MUX4 + 0x01)
#define ADC_MUX6 (ADC_MUX5 + 0x01)
#define ADC_MUX7 (ADC_MUX6 + 0x01)

/**
 * @brief Encloses the ADC protocol. 
 */
namespace Analog {

    /**
     * @brief Operates and reads from the ADC protocol.
     */
    struct Adc {

        /**
         * @brief Allocates a new Instance object.
         * 
         * @return Adc* a pointer reference to an object representing this type.
         */
        static Adc* getInstance() {
            return (Analog::Adc*) calloc(1, sizeof(Analog::Adc*));    
        }

        /**
         * @brief Starts the ADC protocol and enable the adc interrupt service by setting the [ADEN] and [ADIE].
         */
        void startProtocol();
        
        /**
         * @brief Stops the ADC protocol by setting [ADEN] to 0x00 through [ADCSRA = 0x00] and formatting the output pins.
         */
        void stopProtocol();

        /**
         * @brief Starts the Analog to Digital conversion.
         * @note When setting the bit [ADIE] on the [ADCSRA] register, an interrupt service is fired once the conversion is completed.
         * @param PIN the ADC MUX pin to read from.
         */
        void startConversion(const uint8_t& PIN);

        /**
         * @brief Combines the readings of [ADCL] and [ADCH] data registers in a 16-bit software register.
         * @note Default value = 1023, max value = 1023, min value = 0.
         * 
         * @return uint16_t a new 16-bit register representing 10-bit decade data output from the ADC.
         */
        uint16_t analogRead();
    };
}

#endif
