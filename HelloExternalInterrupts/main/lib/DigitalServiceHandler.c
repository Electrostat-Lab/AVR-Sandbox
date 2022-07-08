#include<DigitalServiceHandler.h>

ISR (INT0_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPortCycleCompleted(PORTD);
    GPIO::ExternalInterruptHandler::getInstance()->stopHandlersAt(1 << INT0);
}

ISR (INT1_vect) {
    GPIO::ExternalInterruptHandler::getInstance()->onPortCycleCompleted(PORTD);
    GPIO::ExternalInterruptHandler::getInstance()->stopHandlersAt(1 << INT1);
}

void GPIO::ExternalInterruptHandler::startHandlersAt(const uint8_t& INT_VEC) {
    EIMSK |= INT_VEC;

    sei();
}

void GPIO::ExternalInterruptHandler::stopHandlersAt(const uint8_t& INT_VEC) {
    EIMSK &= ~INT_VEC;
}

void GPIO::ExternalInterruptHandler::stopAllHandlers() {
    stopHandlersAt((1 << INT0) | (1 << INT1));
}

void GPIO::ExternalInterruptHandler::setVectorActivationMode(const uint8_t& INT_VEC, const uint8_t& MODE) {
    EICRA |= MODE << ((INT_VEC - (1 << INT0)) * 2) /* Move the interrupt sense control bits according to the target INT-VEC */;
}