#ifndef MCP3008_SPI
#define MCP3008_SPI

#include<SPI.h>

#define Configuartion uint8_t

/** Define A/D Channels for config byte */
#define CHANNEL_0 ((uint8_t) 0b10000000) 
#define CHANNEL_1 (CHANNEL_0 + 1)
#define CHANNEL_2 (CHANNEL_1 + 1)
#define CHANNEL_3 (CHANNEL_2 + 1)
#define CHANNEL_4 (CHANNEL_3 + 1)
#define CHANNEL_5 (CHANNEL_4 + 1)
#define CHANNEL_6 (CHANNEL_5 + 1)
#define CHANNEL_7 (CHANNEL_6 + 1)


namespace AD {

    static void* MCP3008_INSTANCE = NULL;

    struct MCP3008 {
        
        uint16_t analogData;

        uint16_t isADConversionFinished;

        /**
         * @brief Allocates a static pointer for the MCP3008 struct as a singleton.
         * 
         * @return MCP3008* instance pointer to the MCP3008 struct.
         */
        static MCP3008* getInstance() {
            if (AD::MCP3008_INSTANCE == NULL) {
                AD::MCP3008_INSTANCE = (AD::MCP3008*) calloc(1, sizeof(AD::MCP3008));
            }
            return (AD::MCP3008*) AD::MCP3008_INSTANCE;
        }

        /**
         * @brief Initializes the ADC by bringing CS to LOW and sending the starter bits
         * and the starter clocks.
         * 
         * @param PORT the slave select port.
         * @param SS_PIN the slave select pin.
         */
        void init(volatile uint8_t& PORT, const uint8_t& SS_PIN);

        /**
         * @brief Starts the ADC conversion on a specific channel using a config.
         * 
         * @param config a channel configuration byte.
         */
        void startADConversion(const Configuartion& config);

        /**
         * @brief Starts A/D conversion in a monitor mode, this is the recommended way of 
         * running an ADC.
         * 
         * @param config the channel configuration.
         * @param PORT the slave select port.
         * @param SS_PIN the slave select pin.
         * @param void(*action)(uint16_t&) an action to be invoked after adc conversion.
         */
        void monitorADConversion(const Configuartion& config, volatile uint8_t& PORT, const uint8_t& SS_PIN, void(*action)(uint16_t&));

        /**
         * @brief Ends the A/D conversion by bringing the CS to HIGH.
         * 
         * @param PORT the slave select port.
         * @param SS_PIN the slave select pin.
         */
        void endADConversion(volatile uint8_t& PORT, const uint8_t& SS_PIN);

        /**
         * @brief Get the Analog Data object.
         * 
         * @return uint16_t& analog data read from [SPDR].
         */
        uint16_t& getAnalogData();
    };
}

#endif