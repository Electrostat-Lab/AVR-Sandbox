#include<avr/io.h>

#include<Serial.h>
#include<util/delay.h>
#include<DigitalServiceHandler.h>

void Serial::UART::onDataReceiveCompleted(const uint8_t& data) {

}

void Serial::UART::onDataTransmitCompleted(const uint8_t& data) {

}

void GPIO::ExternalInterruptHandler::onPortCycleCompleted(volatile uint8_t& data) {
    Serial::UART::getInstance()->println(1, 10);
    GPIO::ExternalInterruptHandler::getInstance()->startHandlersAt(1 << INT0);
    PORTD |= (1 << PD2);
}

int main(void) {
    Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600);
    PORTD |= (1 << PD2);
    GPIO::ExternalInterruptHandler::getInstance()->startHandlersAt(1 << INT0);
    
    while (1); // block forever
    return 0;
}
