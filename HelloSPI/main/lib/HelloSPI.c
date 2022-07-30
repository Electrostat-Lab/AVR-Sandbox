#define F_CPU 16000000UL

#include<Serial.h>
#include<util/delay.h>

#define LOW ((const uint8_t) 0x00)
#define HIGH ((const uint8_t) 0xFF)
#define MISO 4
#define MOSI 3
#define SCK 5
#define SS 2

uint8_t starterBit[1] = {1};
uint8_t donotCareBit[1] = {0};

uint8_t configBits[4] = {1, 0, 0, 0};

uint8_t readBits[10];

static inline void writeMOSI(const uint8_t& STATE) {
    if (STATE == LOW) {
        PORTB &= ~(1 << MOSI);
    } else {
        PORTB |= (1 << MOSI);
    }
}

static inline uint16_t& readMISO() {

}

static inline void generateClocks(const uint32_t& count, const uint8_t& delay, uint8_t* fallingEdgeBuffer, uint8_t* risingEdgeBuffer) {
    for (uint8_t i = 0; i < count; i++) {
        /* bring SCK to low */
        // PORTB &= ~(1 << SCK);
        // /* trigger a falling edge listener */
        // if (fallingEdgeBuffer != NULL) {
        //     writeMOSI(PORTB & (fallingEdgeBuffer[i] << MOSI) && (1 << MOSI));
        // }
        // /* delay the LOW time */
        // _delay_us(delay / 1000);

        /* bring SCK to high */
        PORTB |= (1 << SCK);
        /* trigger a rising edge listener */
        if (risingEdgeBuffer != NULL) {
            writeMOSI(PORTB & (risingEdgeBuffer[i] << MOSI) && (1 << MOSI));
        }
        /* delay the HIGH time */
        _delay_us(delay / 1000);
    }
}

static inline void generateClocks2(const uint32_t& count, const uint8_t& delay, uint8_t* readBuffer) {
     for (uint8_t i = 0; i < count; i++) {
        // /* bring SCK to low */
        // PORTB &= ~(1 << SCK);
    
        // /* delay the LOW time */
        // _delay_us(delay / 1000);

        /* bring SCK to high */
        PORTB |= (1 << SCK);
        /* trigger a rising edge listener */
        if (readBuffer != NULL) {
            readBuffer[i] = (PORTB & (1 << MISO)) && (1 << MISO);
        }
        /* delay the HIGH time */
        _delay_us(delay / 1000);
    }
}

static inline void startSPI() {
    Serial::UART::getInstance()->sprintln((char*) "Communication starts...");
    /* set Data Direction register to 1 to enable the target pins as output */
    DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    SPCR |= (1 << SPE) | (1 << MSTR);
    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);
    /* bring CS to low */
    PORTB &= ~(1 << SS);
    _delay_us(100 / 1000);
    
    /* start clock cycles */
    /* Don't Care Starter clocks */
    generateClocks(7, 125, NULL, NULL);
    /* Send the starter bit aligned with the falling edge */
    generateClocks(1, 125, starterBit, donotCareBit);
    /* Send config bits aligned with the falling edge of the clock */
    generateClocks(4, 125, configBits, donotCareBit);
    /* Clock out Null bit and donot care data */
    generateClocks(2, 125, donotCareBit, donotCareBit);
    /* read analog bits */
    generateClocks2(10, 125, readBits);
    for (uint8_t i = 0; i < 10; i++) {
        Serial::UART::getInstance()->println(readBits[i], 10);
    }
    /* bring CS to HIGH */
    PORTB |= (1 << SS);
    _delay_us(270 / 1000);

}

int main (void) {
    Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600_16MHZ);
    while (1) {
        startSPI(); 
    }
    return 0;
}
