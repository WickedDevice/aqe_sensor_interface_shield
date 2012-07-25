/*
 * utility.h
 *
 *  Created on: Jul 24, 2012
 *      Author: vic
 */

#ifndef UTILITY_H_
#define UTILITY_H_

/* TWI constants and prototypes */
#define TWI_SLAVE_ADDRESS               3    // must be less than 127
#define TWI_BUFFER_SIZE                 8
#define TWI_GET_NUM_SENSORS_ATTACHED    0x00 // no parameters
#define TWI_GET_RAW_SENSOR_VALUE        0x11 // parameter = sensor index
#define TWI_GET_CALUCLATED_SENSOR_VALUE 0x22 // parameter = sensor index

#define POWER_LED_PORT PORTB
#define POWER_LED_DDR  DDRB
#define POWER_LED_PIN  2
// macro to work with Power LED
#define POWER_LED 1
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


#define STATUS_LED 0
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

#define ENABLE_NO2_HEATER_PORT PORTD
#define ENABLE_NO2_HEATER_DDR  DDRD
#define ENABLE_NO2_HEATER_PIN  0
// macro to work with NO2 Heater Enable
#define NO2_HEATER_INIT() do{ \
        ENABLE_NO2_HEATER_DDR  |= _BV(ENABLE_NO2_HEATER_PIN); \
        ENABLE_NO2_HEATER_PORT &= ~_BV(ENABLE_NO2_HEATER_PIN); \
    }while(0)
#define ENABLE_NO2_HEATER() do{ \
        ENABLE_NO2_HEATER_PORT |= _BV(ENABLE_NO2_HEATER_PIN); \
    }while(0)
#define DISABLE_NO2_HEATER() do{ \
        ENABLE_NO2_HEATER_PORT &= ~_BV(ENABLE_NO2_HEATER_PIN); \
    }while(0)
#define ENABLE_NO2_HEATER_TOGGLE() do{ \
        ENABLE_NO2_HEATER_PORT ^= _BV(ENABLE_NO2_HEATER_PIN); \
    }while(0)

#define ENABLE_CO_HEATER_PORT PORTD
#define ENABLE_CO_HEATER_DDR  DDRD
#define ENABLE_CO_HEATER_PIN  3
// macro to work with NO2 Heater Enable
#define CO_HEATER_INIT() do{ \
        ENABLE_CO_HEATER_DDR  |= _BV(ENABLE_CO_HEATER_PIN); \
        ENABLE_CO_HEATER_PORT &= ~_BV(ENABLE_CO_HEATER_PIN); \
    }while(0)
#define ENABLE_CO_HEATER() do{ \
        ENABLE_CO_HEATER_PORT |= _BV(ENABLE_CO_HEATER_PIN); \
    }while(0)
#define DISABLE_CO_HEATER() do{ \
        ENABLE_CO_HEATER_PORT &= ~_BV(ENABLE_CO_HEATER_PIN); \
    }while(0)
#define ENABLE_CO_HEATER_TOGGLE() do{ \
        ENABLE_CO_HEATER_PORT ^= _BV(ENABLE_CO_HEATER_PIN); \
    }while(0)

/* Utility constants and prototypes */
void blinkLEDs(uint8_t n, uint8_t which_led);
void delay_sec(uint8_t n);


#endif /* UTILITY_H_ */
