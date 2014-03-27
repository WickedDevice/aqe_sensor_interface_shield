/*
 * utility.h
 *
 *  Created on: Jul 24, 2012
 *      Author: vic
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#define HW_VERSION_1_5
//#define HW_VERSION_1_6

/* TWI constants and prototypes */
#define TWI_SLAVE_ADDRESS               3   // must be less than 127
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


#define NO2_R1_DDR  DDRC
#define NO2_R1_PORT PORTC
#define NO2_R1_PIN  7
// GND output
#define NO2_R2_DISABLE() do{ \
        NO2_R1_DDR  |= _BV(NO2_R1_PIN);\
        NO2_R1_PORT &= ~_BV(NO2_R1_PIN);\
    } while(0);
// high impedance input
#define NO2_R2_ENABLE() do{ \
        NO2_R1_DDR  &= ~_BV(NO2_R1_PIN);\
        NO2_R1_PORT &= ~_BV(NO2_R1_PIN);\
    } while(0);

#define NO2_R2_DDR  DDRD
#define NO2_R2_PORT PORTD
#define NO2_R2_PIN  1
// GND output
#define NO2_R3_DISABLE() do{ \
        NO2_R2_DDR  |= _BV(NO2_R2_PIN);\
        NO2_R2_PORT &= ~_BV(NO2_R2_PIN);\
    } while(0);
// high impedance input
#define NO2_R3_ENABLE() do{ \
        NO2_R2_DDR  &= ~_BV(NO2_R2_PIN);\
        NO2_R2_PORT &= ~_BV(NO2_R2_PIN);\
    } while(0);

#define CO_R1_DDR  DDRD
#define CO_R1_PORT PORTD
#define CO_R1_PIN  4
// GND output
#define CO_R2_DISABLE() do{ \
        CO_R1_DDR  |= _BV(CO_R1_PIN);\
        CO_R1_PORT &= ~_BV(CO_R1_PIN);\
    } while(0);
// high impedance input
#define CO_R2_ENABLE() do{ \
        CO_R1_DDR  &= ~_BV(CO_R1_PIN);\
        CO_R1_PORT &= ~_BV(CO_R1_PIN);\
    } while(0);

#define CO_R2_DDR  DDRB
#define CO_R2_PORT PORTB
#define CO_R2_PIN  7
// GND output
#define CO_R3_DISABLE() do{ \
        CO_R2_DDR  |= _BV(CO_R2_PIN);\
        CO_R2_PORT &= ~_BV(CO_R2_PIN);\
    } while(0);
// high impedance input
#define CO_R3_ENABLE() do{ \
        CO_R2_DDR  &= ~_BV(CO_R2_PIN);\
        CO_R2_PORT &= ~_BV(CO_R2_PIN);\
    } while(0);

// low side resistances in ohms
#define NO2_SENSOR_R1 2200L
#if defined(HW_VERSION_1_5)
#define NO2_SENSOR_R2 0L
#elif defined(HW_VERSION_1_6)
#define NO2_SENSOR_R2 24200L
#else
#define NO2_SENSOR_R2 __error__
#endif
#define NO2_SENSOR_R3 244200L

#define CO_SENSOR_R1  68000L
#define CO_SENSOR_R2  68000L
#define CO_SENSOR_R3  680000L

// divider switchover ADC values
#define NO2_R1R2R3_THRESHOLD   415L // 388L
#define NO2_R1R2_THRESHOLD     226L // 205L
#define CO_R1R2R3_THRESHOLD    761L
#define CO_R1R2_THRESHOLD      363L

#define NO2_VCC_TENTH_VOLTS  2500L
#define CO_VCC_TENTH_VOLTS   5000L
#define ADC_VCC_TENTH_VOLTS  5000L

#define NO2_MIN_ADC_HIGH_R   (36)
#define CO_MIN_ADC_HIGH_R    (360)

/* Utility constants and prototypes */
void blinkLEDs(uint8_t n, uint8_t which_led);
void delay_sec(uint8_t n);
uint16_t byte2uint16(uint8_t high_byte, uint8_t low_byte);
uint8_t uint16_high_byte(uint16_t uint16);
uint8_t uint16_low_byte(uint16_t uint16);

void big_endian_copy_uint32_to_buffer(uint32_t value, uint8_t * buffer);

uint32_t get_r1(uint8_t sensor_index);
uint32_t get_r2(uint8_t sensor_index);
uint32_t get_r3(uint8_t sensor_index);

uint16_t get_r1r2r3_threshold(uint8_t sensor_index);
uint16_t get_r1r2_threshold(uint8_t sensor_index);

uint32_t get_sensor_vcc(uint8_t sensor_index);
uint16_t get_sensor_min_adc_high_r(uint8_t sensor_index);
void SENSOR_R2_ENABLE(uint8_t sensor_index);
void SENSOR_R3_ENABLE(uint8_t sensor_index);
void SENSOR_R2_DISABLE(uint8_t sensor_index);
void SENSOR_R3_DISABLE(uint8_t sensor_index);

uint32_t min32(uint32_t x, uint32_t y);

#endif /* UTILITY_H_ */
