#ifndef DIGITAL_HANDLER 
#define DIGITAL_HANDLER

#include<avr/io.h>
#include<stdlib.h>
#include<avr/interrupt.h>

#define LOW_LEVEL ((const uint8_t) 0b00000000)
#define FALLING_EDGE ((const uint8_t) 0b00000010)
#define RISING_EDGE ((const uint8_t) 0b00000011)
#define ANY_LOGICAL_CHANGE ((const uint8_t) 0b00000001)

namespace GPIO {
    /**
     * @brief Static pointer for the External Interrupt structure.
     */
    static void* INSTANCE = NULL;

    struct ExternalInterruptHandler {

        static ExternalInterruptHandler* getInstance() {
            if (GPIO::INSTANCE == NULL) {
                GPIO::INSTANCE = (GPIO::ExternalInterruptHandler*) calloc(1, sizeof(GPIO::ExternalInterruptHandler*));
            }
            return (GPIO::ExternalInterruptHandler*) GPIO::INSTANCE;
        }

        void startHandlersAt(const uint8_t& INT_VEC);

        void setVectorActivationMode(const uint8_t& INT_VEC, const uint8_t& MODE);

        void stopHandlersAt(const uint8_t& INT_VEC);

        void stopAllHandlers();

        void onPortCycleCompleted(volatile uint8_t& data);
    };
}


#endif