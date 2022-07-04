/**
 * @file Analog.c
 * @author pavl_g.
 * @brief An implementation for the [Analog.h] header file.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<Analog.h>

void Analog::Adc::startProtocol() {
    /* setup ADCSRA */
    ADCSRA = (1 << ADEN) /*enable adc protocol*/ | (1 << ADIE) /*enable interrupt service*/ 
                | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) /*set clock prescaler to clk/128*/; 
}

void Analog::Adc::stopProtocol() {
    ADCH = 0x00;
    ADCL = 0x00;
    ADCSRA = 0x00; /* format the control status register A including the [ADEN] bit */
}

void Analog::Adc::startConversion(const uint8_t& PIN) {
    /* setup ADMUX */
    ADMUX = 0b01000000 | PIN; /* 1 for REFS0 for (VREF = VCC) */
    ADCSRA |= (1 << ADSC); /* the last step: start conversion */
}

uint16_t Analog::Adc::analogRead() { 
    volatile uint8_t adcl = ADCL; /* ADCL must be read before ADCH */
    volatile uint8_t adch = ADCH;
    return ((0x00 | adch) << 8) | adcl; /* concatenate the 2 (8-bit registers) in a 16-bit software register */
}