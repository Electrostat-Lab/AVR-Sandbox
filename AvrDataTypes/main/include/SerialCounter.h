#ifndef SERIAL_C

#define SERIAL_C

#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS

#include<stdint.h>
#include<util/delay.h>

#define HIGH UINT8_C(0b01)

namespace SerialCounter {
    struct Counter {
       void start(volatile uint8_t& PORT, const double& DELAY);
    };
};

#endif
