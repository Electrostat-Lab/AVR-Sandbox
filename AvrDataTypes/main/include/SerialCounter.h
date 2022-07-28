#ifndef SERIAL_C

#define SERIAL_C

#define F_CPU 16000000UL

#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS

#include<stdint.h>
#include<util/delay.h>

#define HIGH UINT8_C(0b01)

/**
 * @brief Instantiates a counter using a software serial clock.
 */
namespace SerialCounter {
	/**
	* @brief Creates a software timer [counter] on a [PORT].
	*/
	struct Counter {
		/**
		* @brief Starts a software timer [counter] on a [PORT].
		* @param PORT the port to count on, could be software/virtual port
		* @param DELAY a delay in ms
		*/
		void start(volatile uint8_t& PORT);
	};
};

#endif
