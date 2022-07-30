#include<SPI.h>
    
ISR (SPI_STC_vect) {
    // Serial::SPI::getInstance()->onDataTransmitCompleted(SPDR);
}

void Serial::SPI::startProtocol(const TransmissionType& transmissionType, const SPIFosc& spiFosc) {

    if (transmissionType == MASTER) {
        /* define user-defined pins as output */
        DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    } else if (transmissionType == SLAVE) {
        PORTB |= (1 << MISO);
    }

    SPCR = 0x00;

    if (spiFosc == Fosc_1_2) {
        /* flip SPR0/1 to zero */
        SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_4) {
        /* flip SPR0/1 to zero */
        SPCR = SPCR & (~(1 << SPR0) & ~(1 << SPR1));
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    } else if (spiFosc == Fosc_1_16) {
        /* flip SPR0 to one and SPR1 to zero */
        SPCR = (SPCR & ~(1 << SPR1)) | (1 << SPR0);
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    } else if (spiFosc == Fosc_1_32) {
        /* flip SPR0 to zero and SPR1 to one */
        SPCR = (SPCR & ~(1 << SPR0)) | (1 << SPR1);
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_64) {
        /* flip SPR0/1 to one */
        SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
        /* flip SPI2X bit to one */
        SPSR |= (1 << SPI2X);
    } else if (spiFosc == Fosc_1_128) {
        /* flip SPR0/1 to one */
        SPCR = SPCR | (1 << SPR0) | (1 << SPR1);
        /* flip SPI2X bit to zero */
        SPSR &= ~(1 << SPI2X);
    }
    /* start the protocol with an interrupt event handler on data transmission */
    SPCR |= (1 << SPE) | (transmissionType) | MODE_0_1;
}

void Serial::SPI::generateSCLK(const uint16_t& count, const uint8_t& width, void(*action)()) {
    for (uint16_t i = 0; i < count; i++) {
        PORTB &= ~(1 << SCK);
        _delay_us(width / 1000);
        PORTB |= (1 << SCK);
        if (action != NULL) {
            action();
        }
        _delay_us(width / 1000);
    }
}

void Serial::SPI::resetSlaveSelect(volatile uint8_t& PORT, const uint8_t& PIN) {
    _delay_us(100 / 1000);
    PORT |= (1 << PIN);
    _delay_us(270 / 1000);
    PORT &= ~(1 << PIN);
}

void Serial::SPI::startSPIISR() {
    SPCR |= (1 << SPIE);
    sei();
}

void Serial::SPI::stopSPIISR() {
    SPCR &= ~(1 << SPIE);
}

void Serial::SPI::stopProtocol() {
    SPCR &= ~(1 << SPE);
}

void Serial::SPI::write(const uint8_t& data) {
    SPDR = data;
    while (!isTransmissionCompleted());
}

void Serial::SPI::disablePowerReductionRegister() {
    PRR &= ~(1 << PRSPI);
}

volatile uint8_t& Serial::SPI::getTransmittedData() {
    return transmittedData;
}