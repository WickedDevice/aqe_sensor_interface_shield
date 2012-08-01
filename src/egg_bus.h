/*
 * egg_bus.h
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#ifndef EGG_BUS_H_
#define EGG_BUS_H_

#include <stdint.h>

#define EGG_BUS_COMMAND_READ        0x11
#define EGG_BUS_COMMAND_WRITE       0x33

#define EGG_BUS_NUM_HOSTED_SENSORS  2

#define EGG_BUS_MAX_RESPONSE_LENGTH 16

/* Sensor Module Memory Map Definition */

// Header Definitions
#define EGG_BUS_ADDRESS_SENSOR_COUNT      0
#define EGG_BUS_ADDRESS_MODULE_ID         1

// Sensor Block Definitions
#define EGG_BUS_SENSOR_BLOCK_BASE_ADDRESS             32
#define EGG_BUS_SENSOR_BLOCK_SIZE                     256
#define EGG_BUS_SENSOR_BLOCK_TYPE_OFFSET              0
#define EGG_BUS_SENSOR_BLOCK_UNITS_OFFSET             16
#define EGG_BUS_SENSOR_BLOCK_R0_OFFSET                32
#define EGG_BUS_SENSOR_BLOCK_COMPUTED_VALUE_OFFSET    36
#define EGG_BUS_SENSOR_BLOCK_UNITS_MULTIPLIER_OFFSET  40
// #define EGG_BUS_SENSOR_BLOCK_SPARE_OFFSET          44
#define EGG_BUS_SENSOR_BLOCK_RESPONSE_CURVE           64

// Debug Block Definitions
#define EGG_BUS_DEBUG_BLOCK_BASE_ADDRESS              65408
#define EGG_BUS_DEBUG_HEATER_VOLTAGE_PLUS             65408
#define EGG_BUS_DEBUG_HEATER_VOLTAGE_MINUS            65412
#define EGG_BUS_DEBUG_HEATER_POWER_MW                 65416

uint16_t egg_bus_get_read_address();
uint8_t egg_bus_map_to_analog_pin(uint8_t sensor_index);
void egg_bus_set_read_address(uint16_t read_address);
void egg_bus_get_sensor_type(uint8_t sensor_index, char * target_buffer);
void egg_bus_get_sensor_units(uint8_t sensor_index, char * target_buffer);
uint32_t egg_bus_get_r0_kohms(uint8_t sensor_index);

#endif /* EGG_BUS_H_ */
