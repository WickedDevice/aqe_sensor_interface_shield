/*
 * egg_bus.c
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#include <stdint.h>

uint8_t egg_bus_command_received = 0;
uint8_t egg_bus_sensor_index_requested = 0;

uint8_t egg_bus_get_command_received(){
    return egg_bus_command_received;
}

uint8_t egg_bus_get_sensor_index_requested(){
    return egg_bus_sensor_index_requested;
}

void egg_bus_set_command_received(uint8_t cmd){
    egg_bus_command_received = cmd;
}

void egg_bus_set_sensor_index_requested(uint8_t sensor_idx){
    egg_bus_sensor_index_requested = sensor_idx;
}
