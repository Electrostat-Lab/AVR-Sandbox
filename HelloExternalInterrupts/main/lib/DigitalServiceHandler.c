/**
 * @file DigitalServiceHandler.c
 * @author pavl_g.
 * @brief Operates and controls the external interrupt service handlers for the pin change operations for atmega328p.
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<DigitalServiceHandler.h>

ISR (INT0_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (INT1_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (PCINT0_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (PCINT1_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

ISR (PCINT2_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPinChanged();
}

void GPIO::ExternalInterruptHandler::activateINT(const uint8_t& INT_VEC) {
    EIMSK |= INT_VEC;
    EICRA = 0b0000101;

    sei();
}

void GPIO::ExternalInterruptHandler::activatePCINT0(const uint8_t& INT_VEC) {
    PCICR |= (1 << PCIE0);
    PCMSK0 |= INT_VEC;

    sei();
}

void GPIO::ExternalInterruptHandler::activatePCINT1(const uint8_t& INT_VEC) {
    PCICR |= (1 << PCIE1);
    PCMSK1 |= INT_VEC;

    sei();
}

void GPIO::ExternalInterruptHandler::activatePCINT2(const uint8_t& INT_VEC) {
    PCICR |= (1 << PCIE2);
    PCMSK2 |= INT_VEC;

    sei();
}

void GPIO::ExternalInterruptHandler::stopINT(const uint8_t& INT_VEC) {
    EIMSK &= ~INT_VEC;
}

void GPIO::ExternalInterruptHandler::stopPCINT0(const uint8_t& INT_VEC) {
    PCMSK0 &= ~INT_VEC;
}

void GPIO::ExternalInterruptHandler::stopPCINT1(const uint8_t& INT_VEC) {
    PCMSK1 &= ~INT_VEC;
}

void GPIO::ExternalInterruptHandler::stopPCINT2(const uint8_t& INT_VEC) {
    PCMSK2 &= ~INT_VEC;
}

void GPIO::ExternalInterruptHandler::stopAllHandlers() {
    /* (1 << INT0) | (1 << INT1) */
    stopINT(0b11);
    /* (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) ..... = 0xFF*/
    stopPCINT0(0xFF);
    /* (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) ..... = 0xFF*/
    stopPCINT1(0xFF);
    /* (1 << PCINT16) | (1 << PCINT17) | (1 << PCINT18) ..... = 0xFF*/
    stopPCINT2(0xFF);
}