#include<Register.h>

size_t Register::Register8::getLength() {
    return sizeof(PORT) / sizeof(typeof(*PORT));
}

void Register::Register8::digitalWrite(volatile uint8_t& PORT, const uint8_t& PIN, const uint8_t& STATE) {
    uint8_t* BIT = (uint8_t*) calloc(1, sizeof(uint8_t*));
    *BIT = (HIGH << PIN);
    if (STATE >= HIGH) {
        PORT |= *BIT;
    } else {
        PORT &= ~(*BIT);
    }
    free(BIT);
}

const uint8_t Register::Register8::digitalRead(volatile uint8_t& PORT, const uint8_t& PIN) {
    const uint8_t BIT = HIGH << PIN; /* e.g: 0b00000001 << 5 = 0b00010000 */
    return PORT & BIT;
}