/**
 * @file Serial.c
 * @author pavl_g.
 * @brief An implementation for the [Serial.h] header file for AtMega32A.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<Serial.h>

/**
 * @brief Triggered when the RXC0 is settled and the receiving has been completed.
 */
ISR (__vector_USART_RX) {
    Serial::UART::getInstance()->onDataReceiveCompleted(Serial::UART::getInstance()->readASCII());
}

/**
 * @brief Triggered when the bit UDRE0 is one (the data register buffer is empty).
 */
ISR (USART_UDRE_vect) {
    REG_UDR = *(Serial::UART::getInstance()->transmitData);
    Serial::UART::getInstance()->stopDataRegisterEmptyBufferISR();
}

/**
 * @brief Triggered when the bit TXC is settled and the data transmission has been completed.
 */
ISR (__vector_UART_TX) {
    Serial::UART::getInstance()->onDataTransmitCompleted((const uint8_t) REG_UDR);
    Serial::UART::getInstance()->stopTransmitterISR();
}

void Serial::UART::startProtocol(const uint8_t& BAUD_RATE_VAL) {
    REG_UCSRB = (1 << BIT_TXEN) | (1 << BIT_RXEN); /* enable the transmit and receiver buffers and their interrupt services */
    REG_UCSRC = (1 << BIT_USBS) | (3 << BIT_UCSZ0); // enables the UCSZ0, UCSZ1 and URSEL
    REG_UBRRL = BAUD_RATE_VAL; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
    startReceiverISR();
}

void Serial::UART::startDataRegisterEmptyBufferISR() {
    REG_UCSRB |= (1 << BIT_UDRIE);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::startReceiverISR() {
    REG_UCSRB |= (1 << BIT_RXCIE);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopReceiverISR() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_RXCIE); 
}

void Serial::UART::startTransmitterISR() {
    REG_UCSRB |= (1 << BIT_TXCIE);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopTransmitterISR() {
    // Finds the 1s complement of all bits in TXCIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_TXCIE); 
}

void Serial::UART::stopDataRegisterEmptyBufferISR() {
    // Finds the 1s complement of all bits in UDRIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_UDRIE); 
}

void Serial::UART::stopProtocol() {
    REG_UCSRB = 0x00; 
}

void Serial::UART::setTransmitDataRegister(const uint8_t& transmitData) {
    *(this->transmitData) = transmitData;
    startDataRegisterEmptyBufferISR();
    startTransmitterISR();
}

uint8_t Serial::UART::readASCII() {
    while (!(REG_UCSRA & (1 << BIT_RXC)));
    return REG_UDR;
}
 
void Serial::UART::cprint(char& data) {
    while (!(REG_UCSRA & (1 << BIT_UDRE)));
    REG_UDR = data;
    startTransmitterISR();
}

void Serial::UART::cprintln(char& data) {
    cprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}

void Serial::UART::sprint(char* data) {
    int i = 0;
    while (i < strlen(data)) {
        cprint(data[i++]);
    }
}

void Serial::UART::sprintln(char* data) {
    sprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}

void Serial::UART::print(const int64_t& data, const uint8_t& base) {
    char* strBuffer = allocateStringBuffer();
    // convert input to string
    itoa(data, strBuffer, base);
    int i = 0;
    while (i < strlen(strBuffer)) {
        cprint(strBuffer[i++]);
    }
    free(strBuffer);
}

void Serial::UART::println(const int64_t& data, const uint8_t& base) {
    print(data, base);
    sprint(NEW_LINE_CARRIAGE_R);
}