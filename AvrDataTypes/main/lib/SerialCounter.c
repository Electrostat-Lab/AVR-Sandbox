#include<SerialCounter.h>

void SerialCounter::Counter::start(volatile uint8_t& PORT, const double& DELAY) {
    volatile uint8_t CLK = 0x00;
    while(HIGH) {
	_delay_ms(DELAY/2);
	PORT = HIGH << (++CLK % UINT8_MAX);
	_delay_ms(DELAY/2);
    }
}
