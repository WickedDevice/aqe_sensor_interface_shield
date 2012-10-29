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

#define EGG_BUS_FIRMWARE_VERSION_NUMBER   0x00000003

// Header Definitions
#define EGG_BUS_ADDRESS_SENSOR_COUNT      0
#define EGG_BUS_ADDRESS_MODULE_ID         1
#define EGG_BUS_FIRMWARE_VERSION          7

// Sensor Block Definitions
#define EGG_BUS_SENSOR_BLOCK_BASE_ADDRESS             32
#define EGG_BUS_SENSOR_BLOCK_SIZE                     256
#define EGG_BUS_SENSOR_BLOCK_TYPE_OFFSET              0
#define EGG_BUS_SENSOR_BLOCK_UNITS_OFFSET             16
#define EGG_BUS_SENSOR_BLOCK_R0_OFFSET                32
#define EGG_BUS_SENSOR_BLOCK_MEASURED_INDEPENDENT_OFFSET     36
#define EGG_BUS_SENSOR_BLOCK_TABLE_X_SCALER_OFFSET    40
#define EGG_BUS_SENSOR_BLOCK_RAW_VALUE_OFFSET         44
#define EGG_BUS_SENSOR_BLOCK_TABLE_Y_SCALER_OFFSET    48
#define EGG_BUS_SENSOR_BLOCK_MEASURED_INDEPENDENT_SCALER_OFFSET 52
#define EGG_BUS_SENSOR_BLOCK_COMPUTED_VALUE_MAPPING_TABLE_BASE_OFFSET 56

// Debug Block Definitions
#define EGG_BUS_DEBUG_BLOCK_BASE_ADDRESS              65408
#define EGG_BUS_DEBUG_NO2_HEATER_VOLTAGE_PLUS         65408
#define EGG_BUS_DEBUG_NO2_HEATER_VOLTAGE_MINUS        65412
#define EGG_BUS_DEBUG_NO2_HEATER_POWER_MW             65416
#define EGG_BUS_DEBUG_NO2_DIGIPOT_WIPER               65420
#define EGG_BUS_DEBUG_CO_HEATER_VOLTAGE_PLUS          65424
#define EGG_BUS_DEBUG_CO_HEATER_VOLTAGE_MINUS         65428
#define EGG_BUS_DEBUG_CO_HEATER_POWER_MW              65432
#define EGG_BUS_DEBUG_CO_DIGIPOT_WIPER                65436
#define EGG_BUS_DEBUG_DIGIPOT_STATUS                  65440

uint16_t egg_bus_get_read_address();
uint8_t egg_bus_map_to_analog_pin(uint8_t sensor_index);
void egg_bus_set_read_address(uint16_t read_address);
void egg_bus_get_sensor_type(uint8_t sensor_index, char * target_buffer);
void egg_bus_get_sensor_units(uint8_t sensor_index, char * target_buffer);
uint32_t egg_bus_get_r0_ohms(uint8_t sensor_index);
void egg_bus_set_r0_ohms(uint8_t sensor_index, uint32_t value);

#endif /* EGG_BUS_H_ */
