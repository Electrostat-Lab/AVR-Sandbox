/**
 * @file DigitalServiceHandler.h
 * @author pavl_g.
 * @brief Operates the digital external interrupt services for atmega328p.
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DIGITAL_HANDLER 
#define DIGITAL_HANDLER

#include<avr/io.h>
#include<stdlib.h>
#include<avr/interrupt.h>

/** 
 * Define booleans for different channels, 
 * find more at the ATMEGA328p datasheet the external interrupt section .
 */

/** EIMSK register bits */
#define isINT0Active() ((volatile uint8_t) PORTD & (1 << PD2))
#define isINT1Active() ((volatile uint8_t) PORTD & (1 << PD3))

/** PCMSK0 register bits */
#define isPCINT0Active() ((volatile uint8_t) PORTB & (1 << PB0))
#define isPCINT1Active() ((volatile uint8_t) PORTB & (1 << PB1))
#define isPCINT2Active() ((volatile uint8_t) PORTB & (1 << PB2))
#define isPCINT3Active() ((volatile uint8_t) PORTB & (1 << PB3))
#define isPCINT4Active() ((volatile uint8_t) PORTB & (1 << PB4))
#define isPCINT5Active() ((volatile uint8_t) PORTB & (1 << PB5))
#define isPCINT6Active() ((volatile uint8_t) PORTB & (1 << PB6))
#define isPCINT7Active() ((volatile uint8_t) PORTB & (1 << PB7))

/** PCMSK1 register bits */
#define isPCINT8Active() ((volatile uint8_t) PORTC & (1 << PC0))
#define isPCINT9Active() ((volatile uint8_t) PORTC & (1 << PC1))
#define isPCINT10Active() ((volatile uint8_t) PORTC & (1 << PC2))
#define isPCINT11Active() ((volatile uint8_t) PORTC & (1 << PC3))
#define isPCINT12Active() ((volatile uint8_t) PORTC & (1 << PC4))
#define isPCINT13Active() ((volatile uint8_t) PORTC & (1 << PC5))
#define isPCINT14Active() ((volatile uint8_t) PORTC & (1 << PC6))

/** PCMSK2 register bits */
#define isPCINT16Active() ((volatile uint8_t) PORTD & (1 << PD0))
#define isPCINT17Active() ((volatile uint8_t) PORTD & (1 << PD1))
#define isPCINT18Active() ((volatile uint8_t) PORTD & (1 << PD2))
#define isPCINT19Active() ((volatile uint8_t) PORTD & (1 << PD3))
#define isPCINT20Active() ((volatile uint8_t) PORTD & (1 << PD4))
#define isPCINT21Active() ((volatile uint8_t) PORTD & (1 << PD5))
#define isPCINT22Active() ((volatile uint8_t) PORTD & (1 << PD6))
#define isPCINT23Active() ((volatile uint8_t) PORTD & (1 << PD7))

/**
 * @brief Defines a GPIO space.
 */
namespace GPIO {
    /**
     * @brief Static pointer for the External Interrupt structure.
     */
    static void* INSTANCE = NULL;

    struct ExternalInterruptHandler {

        static ExternalInterruptHandler* getInstance() {
            if (GPIO::INSTANCE == NULL) {
                GPIO::INSTANCE = (GPIO::ExternalInterruptHandler*) calloc(1, sizeof(GPIO::ExternalInterruptHandler*));
            }
            return (GPIO::ExternalInterruptHandler*) GPIO::INSTANCE;
        }

        /**
         * @brief Activates an external interrupt vector from the (EIMSK) register.
         * 
         * @param INT_VEC the bit to activate, either (1 << INT0) or (1 << INT1) or both ((1 << INT0) | (1 << INT1)).
         */
        void activateINT(const uint8_t& INT_VEC);

        /**
         * @brief Activates an external pin change interrupt vector on the (PCMSK0) register.
         * 
         * @param INT_VEC the bit to activate, eg: ((1 << PCINT0..7) | (1 << PCINT0..7) | ...).
         */
        void activatePCINT0(const uint8_t& INT_VEC);

        /**
         * @brief Activates an external pin change interrupt vector on the (PCMSK1) register.
         * 
         * @param INT_VEC the bit to activate, eg: ((1 << PCINT8..14) | (1 << PCINT8..14) | ...).
         */
        void activatePCINT1(const uint8_t& INT_VEC);

        /**
         * @brief Activates an external pin change interrupt vector on the (PCMSK2) register.
         * 
         * @param INT_VEC the bit to activate, eg: ((1 << PCINT16..23) | (1 << PCINT16..23) | ...).
         */
        void activatePCINT2(const uint8_t& INT_VEC);

        /**
         * @brief Stops an external interrupt vector at the (EIMSK) register.
         * 
         * @param INT_VEC the bit to stop, either (1 << INT0) or (1 << INT1) or both ((1 << INT0) | (1 << INT1)).
         */
        void stopINT(const uint8_t& INT_VEC);

        /**
         * @brief Stops an external pin change interrupt vector at the (PCMSK0) register.
         * 
         * @param INT_VEC the bit to stop, eg: ((1 << PCINT0..7) | (1 << PCINT0..7) | ...).
         */
        void stopPCINT0(const uint8_t& INT_VEC);

        /**
         * @brief Stops an external pin change interrupt vector at the (PCMSK1) register.
         * 
         * @param INT_VEC the bit to stop, eg: ((1 << PCINT8..14) | (1 << PCINT8..14) | ...).
         */
        void stopPCINT1(const uint8_t& INT_VEC);

        /**
         * @brief Stops an external pin change interrupt vector at the (PCMSK2) register.
         * 
         * @param INT_VEC the bit to stop, eg: ((1 << PCINT16..23) | (1 << PCINT16..23) | ...).
         */
        void stopPCINT2(const uint8_t& INT_VEC);

        /**
         * @brief Stops all external interrupt handlers for atmega328p.
         */
        void stopAllHandlers();

        /**
         * @brief Triggered when the PIN state changes from an external mean (aka Digial Input)
         * either from LOW to HIGH (RISING EDGE -- LOGIC LOW) or from HIGH to LOW (FALLING EDGE -- LOGIC HIGH).
         */
        void onPinChanged();
    };
}


#endif