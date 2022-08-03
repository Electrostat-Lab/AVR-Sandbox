#include<MCP3008/MCP3008.h>

void AD::MCP3008::init(volatile uint8_t& PORT, const uint8_t& SS_PIN) {
    
    isADConversionFinished = 0;

     /* start protocol */
    Serial::SPI::getInstance()->startProtocol(MASTER, Fosc_1_4, MODE_0_0);
    
    /* bring CS or SS to low to start this slave communication */
    PORTB &= ~(SS_PIN);
    _delay_us(100 / 1000);

    /* send starter bits */
    Serial::SPI::getInstance()->write(0b00000001);

    /* clock out the data to the A/D IC */
    Serial::SPI::getInstance()->generateSCLK(8, 125);
}

void AD::MCP3008::startADConversion(const Configuartion& config) {

    /* start A/D conversion on a CHANNEL */
    Serial::SPI::getInstance()->write(config);

    /* clock out config to the A/D IC */
    Serial::SPI::getInstance()->generateSCLK(8, 125);

    /* remove NULL bit (bit no.3) from the first data frame and shift first frame 8-bits to the left */
    analogData = (SPDR & 0b0000011) << 8;

    /* clock to read the 2nd data frame */
    Serial::SPI::getInstance()->generateSCLK(8, 125);

    /* add the data frame to the uint16_t bit data buffer */
    analogData |= SPDR;

    isADConversionFinished = 1;
}

void AD::MCP3008::monitorADConversion(const Configuartion& config, volatile uint8_t& PORT, const uint8_t& SS_PIN, void(*action)(uint16_t&)) {
    while (1) {
        /* initialize the MCP */
        init(PORT, SS_PIN);
        /* start A/D conversion on a CHANNEL */
        startADConversion(config);
        /* fire an observer */
        if (action != NULL) {
            action(analogData);
        }
        /* end A/D conversion */
        endADConversion(PORT, SS_PIN);
    }
}

void AD::MCP3008::endADConversion(volatile uint8_t& PORT, const uint8_t& SS_PIN) {
    /* finish A/D conversion by bringing the CS to high */
    PORT |= SS_PIN;
    _delay_us(270 / 1000);
}

uint16_t& AD::MCP3008::getAnalogData() {
    return analogData;
}