#define F_CPU 16000000UL

#include<Serial.h>
#include<util/delay.h>
#include<MCP3008/MCP3008.h>

#define SS_PIN 2

void Serial::SPI::onDataTransmitCompleted(volatile uint8_t& data) { }

void Serial::UART::onDataReceiveCompleted(const uint8_t& data) { }

void Serial::UART::onDataTransmitCompleted(const uint8_t& data) { }

static inline void invoke(uint16_t& data) {
    Serial::UART::getInstance()->println(data, 10);
}

int main (void) {
    Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600_16MHZ);
    Serial::UART::getInstance()->sprintln((char*) "Communication starts...");
   
    /* set slave select as output */
    DDRB |= (1 << SS_PIN);
    /* start adc monitoring */
    AD::MCP3008::getInstance()->monitorADConversion(CHANNEL_0, PORTB, (1 << SS_PIN), &invoke);

    return 0;
}