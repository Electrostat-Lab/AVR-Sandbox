#ifndef SPI_PROTOCOL

#define SPI_PROTOCOL
#define F_CPU 16000000UL

#include<avr/io.h>
#include<stdlib.h>
#include<avr/interrupt.h>
#include<util/delay.h>

/** Defines a boolean type */
#define boolean uint8_t

/** Defines the [TransmissionType] datatype */
#define TransmissionType int

/** Defines the [SPIFosc] datatype */
#define SPIFosc float

#define ModeOfTransmission uint8_t

/** Defines the [MASTER] and [SLAVE] transmission modes */
#define MASTER (TransmissionType (1 << MSTR))
#define SLAVE (TransmissionType (SPCR & ~(1 << MSTR)))

/** Defines boolean flags */
#define isTransmissionCompleted() ((boolean) (SPSR & (1 << SPIF)))
#define isSPIEnabled() ((boolean) (SPSR & (1 << SPE)))
#define isDataCollisionWritten() ((boolean) (SPSR & (1 << WCOL)))

/** Defines the SPI rate with respect to the Fosc */
#define Fosc_1_4  ((SPIFosc) 0.25)
#define Fosc_1_16 ((SPIFosc) 1/16)
#define Fosc_1_64 ((SPIFosc) 1/64)
#define Fosc_1_128 ((SPIFosc) 1/128)
#define Fosc_1_2 ((SPIFosc) 0.5)
#define Fosc_1_32 ((SPIFosc) 1/32)

/** Serial Data modes sampling */
#define MODE_0_0 (ModeOfTransmission (SPCR & (~(1 << CPOL) & ~(1 << CPHA))))
#define MODE_0_1 (ModeOfTransmission (SPCR & (~(1 << CPOL) | (1 << CPHA))))
#define MODE_1_0 (ModeOfTransmission (SPCR & ((1 << CPOL) & ~(1 << CPHA))))
#define MODE_1_1 (ModeOfTransmission (SPCR & ((1 << CPOL) | ((1 << CPHA))))

/** Define SPI pins according to the device and the datasheet */
#if defined (__AVR_ATmega32__)
#   define MISO 6
#   define MOSI 5
#   define SCK 7
#elif defined (__AVR_ATmega328P__)
#   define MISO 4
#   define MOSI 3
#   define SCK 5
#endif 

namespace Serial {
    
    /**
     * @warning Internal use only.
     * 
     * @brief An empty buffer to allocate a static pointer for the [Serial::SPI] structure.
     */
    static void* SPI_INSTANCE = NULL;

    struct SPI {

        /**
         * @brief Allocates a new SPI pointer.
         * 
         * @return Serial::SPI* a new SPI pointer reference.
         */
        static Serial::SPI* getInstance() {
            if (Serial::SPI_INSTANCE == NULL) {
                Serial::SPI_INSTANCE = (Serial::SPI*) calloc(1, sizeof(Serial::SPI*));
            }
            return (Serial::SPI*) Serial::SPI_INSTANCE;
        }   

        /**
         * @brief Starts the SPI protocol enabling both the SPE bit (SPI Enable) and the SPIE (SPI Interrupt Enable).
         * 
         * @param transmissionType the transmission type either [MASTER] or [SLAVE], [SLAVE] operates in sleep mode
         * until the mcu receives external clk from a master source.
         * @param spiFosc the spi bit rate.
         * @param MODE the mode of transmission, either [SPI-MODE-0 (0, 0)]-[SPI-MODE-1 (0, 1)]-
         * [SPI-MODE-2 (1, 0)]-[SPI-MODE-3 (1, 1)].
         */
        void startProtocol(const TransmissionType& transmissionType, const SPIFosc& spiFosc, const ModeOfTransmission& MODE);

        /**
         * @brief Generates Serial Clocks with [width] and [count].
         * 
         * @param count the number of clocks in integers.
         * @param width the width of clocks in nano-seconds.
         */
        void generateSCLK(const uint32_t& count, const uint8_t& width);

        /**
         * @brief Starts the SPI interrupt service routine.
         */
        void startSPIISR();

        /**
         * @brief Stops the SPI interrupt service routine.
         */
        void stopSPIISR();

        /**
         * @brief Stops the SPI protocol by disabling the bit [SPE] in register [SPCR].
         */
        void stopProtocol();

        /**
         * @brief Writes an 8-bit number to the SPI data register using the polling method.
         * 
         * @param data an 8-bit data to write to the data register [SPDR].
         */
        void write(const uint8_t& data);

        /**
         * @brief Gets the Transmitted Data object
         * 
         * @return const uint8_t& an 8-bit representation of the transmitted data.
         */
        volatile uint8_t& getTransmittedData();

        /**
         * @brief Fired whenever an interrupt event handler is invoked when the flag [SPIF] is enabled and the [SPIE] bit is enabled.
         */
        void onDataTransmitCompleted(volatile uint8_t& data);

        /**
         * @brief Disables the SPI power reduction bit.
         */
        void disablePowerReductionRegister();   

    };
}


#endif