/*
 * egg_bus.h
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#ifndef EGG_BUS_H_
#define EGG_BUS_H_

#include <stdint.h>

#define EGG_BUS_COMMAND_SENSOR_COUNT         0x00
#define EGG_BUS_COMMAND_GET_RAW_VALUE        0x11
#define EGG_BUS_COMMAND_GET_CALCULATED_VALUE 0x22

#define EGG_BUS_NUM_HOSTED_SENSORS           2

uint8_t egg_bus_get_command_received();
uint8_t egg_bus_get_sensor_index_requested();
void    egg_bus_set_command_received(uint8_t cmd);
void    egg_bus_set_sensor_index_requested(uint8_t sensor_idx);
uint8_t egg_bus_map_to_analog_pin(uint8_t sensor_index);

#endif /* EGG_BUS_H_ */
