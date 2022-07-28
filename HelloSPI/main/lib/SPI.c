#include<SPI.h>
    
ISR (SPI_STC_vect) {
    Serial::SPI::getInstance()->onDataTransmitCompleted(SPDR);
}

void Serial::SPI::startProtocol(const TransmissionType& transmissionType, const SPIFosc& spiFosc) {

    if (transmissionType == MASTER) {
        /* define user-defined pins as output */
        PORTB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
        /* Pull SS down to initiate data connection */
        PORTB &= ~(1 << SS);
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
    SPCR |= (1 << SPE) | (transmissionType) | MODE_0_0;
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

volatile uint8_t& Serial::SPI::read() {
    while (!isTransmissionCompleted());
    return SPDR;
}

void Serial::SPI::disablePowerReductionRegister() {
    PRR &= ~(1 << PRSPI);
}