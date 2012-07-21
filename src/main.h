/*
 * main.h
 *
 *  Created on: Jul 14, 2012
 *      Author: vic
 */

#ifndef MAIN_H_
#define MAIN_H_

#define NUM_SENSORS_SUPPORTED 2 // the number of sensors the slave handles

#define POWER_LED_PORT PORTB
#define POWER_LED_DDR  DDRB
#define POWER_LED_PIN  2
// macro to work with Power LED
#define POWER_LED_INIT() do{ \
        POWER_LED_DDR  |= _BV(POWER_LED_PIN); \
        POWER_LED_PORT &= ~_BV(POWER_LED_PIN); \
    }while(0)
#define POWER_LED_ON() do{ \
        POWER_LED_PORT |= _BV(POWER_LED_PIN); \
    }while(0)
#define POWER_LED_OFF() do{ \
        POWER_LED_PORT &= ~_BV(POWER_LED_PIN); \
    }while(0)
#define POWER_LED_TOGGLE() do{ \
        POWER_LED_PORT ^= _BV(POWER_LED_PIN); \
    }while(0)

#define STATUS_LED_PORT PORTB
#define STATUS_LED_DDR  DDRB
#define STATUS_LED_PIN  1
// macro to work with Status LED
#define STATUS_LED_INIT() do{ \
        STATUS_LED_DDR  |= _BV(STATUS_LED_PIN); \
        STATUS_LED_PORT &= ~_BV(STATUS_LED_PIN); \
    }while(0)
#define STATUS_LED_ON() do{ \
        STATUS_LED_PORT |= _BV(STATUS_LED_PIN); \
    }while(0)
#define STATUS_LED_OFF() do{ \
        STATUS_LED_PORT &= ~_BV(STATUS_LED_PIN); \
    }while(0)
#define STATUS_LED_TOGGLE() do{ \
        STATUS_LED_PORT ^= _BV(STATUS_LED_PIN); \
    }while(0)

#endif /* MAIN_H_ */
