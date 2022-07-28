#define F_CPU 16000000UL

#include<SPI.h>
#include<Serial.h>
#include<util/delay.h>

static Serial::SPI* SPI_INSTANCE_ = Serial::SPI::getInstance();
static Serial::UART* UART_INSTANCE_ = Serial::UART::getInstance();

static inline void initUART() {
    UART_INSTANCE_->startProtocol(BAUD_RATE_57600_16MHZ);
}

static inline void initSPIMasterMode() {
    SPI_INSTANCE_->disablePowerReductionRegister();

    SPI_INSTANCE_->startProtocol(MASTER, Fosc_1_128);
    UART_INSTANCE_->sprintln((char*) "SPI Initialized as MASTER...");
}

void Serial::SPI::onDataTransmitCompleted(volatile uint8_t& data) {
    UART_INSTANCE_->println(data, 10);
    SPI_INSTANCE_->stopSPIISR();
    reti();
}

int main (void) {
    initUART();
    initSPIMasterMode();
    while (true) {
        SPI_INSTANCE_->startSPIISR();
        SPI_INSTANCE_->write(0b00000001);
    }
    return 0;
}
