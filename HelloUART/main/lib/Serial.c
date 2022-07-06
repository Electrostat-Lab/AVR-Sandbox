/**
 * @file Serial.c
 * @author pavl_g.
 * @brief An implementation for the [Serial.h] header file.
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
ISR (USART_RX_vect) {
    Serial::UART::getInstance()->onDataReceiveCompleted(Serial::UART::getInstance()->readASCII());
}

/**
 * @brief Triggered when the bit UDRE0 is one (the data register buffer is empty).
 */
ISR (USART_UDRE_vect) {
    UDR0 = *(Serial::UART::getInstance()->transmitData);
    Serial::UART::getInstance()->stopDataRegisterEmptyBufferISR();
}

/**
 * @brief Triggered when the bit TXC is settled and the data transmission has been completed.
 */
ISR (USART_TX_vect) {
    Serial::UART::getInstance()->onDataTransmitCompleted((const uint8_t) UDR0);
    Serial::UART::getInstance()->stopTransmitterISR();
}

void Serial::UART::startProtocol(const uint8_t& BAUD_RATE_VAL) {
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); /* enable the transmit and receiver buffers and their interrupt services */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // enables the UCSZ0, UCSZ1 and URSEL
    UBRR0 = BAUD_RATE_VAL; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
    startReceiverISR();
}

void Serial::UART::startDataRegisterEmptyBufferISR() {
    UCSR0B |= (1 << UDRIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::startReceiverISR() {
    UCSR0B |= (1 << RXCIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopReceiverISR() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << RXCIE0); 
}

void Serial::UART::startTransmitterISR() {
    UCSR0B |= (1 << TXCIE0);
    /* start the interrupt service handlers */
    sei();
}

void Serial::UART::stopTransmitterISR() {
    // Finds the 1s complement of all bits in TXCIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << TXCIE0); 
}

void Serial::UART::stopDataRegisterEmptyBufferISR() {
    // Finds the 1s complement of all bits in UDRIE0 ---> eg: 0b11111101
    UCSR0B &= ~(1 << UDRIE0); 
}

void Serial::UART::stopProtocol() {
    UCSR0B = 0x00; 
}

void Serial::UART::setTransmitDataRegister(const uint8_t& transmitData) {
    *(this->transmitData) = transmitData;
    startDataRegisterEmptyBufferISR();
    startTransmitterISR();
}

uint8_t Serial::UART::readASCII() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
 
void Serial::UART::cprint(char& data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
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