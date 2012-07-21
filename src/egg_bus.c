/*
 * egg_bus.c
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#include <stdint.h>
#include "egg_bus.h"

static uint8_t egg_bus_command_received = 0;
static uint8_t egg_bus_sensor_index_requested = 0;
static uint8_t egg_bus_sensor_mapping_table[EGG_BUS_NUM_HOSTED_SENSORS] = {
        0, // index 0 [NO2] is on ADC0
        2, // index 1 [CO] is on  ADC2
};

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

uint8_t egg_bus_map_to_analog_pin(uint8_t sensor_index){
    uint8_t analog_pin_number = 0;
    if(sensor_index < EGG_BUS_NUM_HOSTED_SENSORS){
        analog_pin_number = egg_bus_sensor_mapping_table[sensor_index];
    }
    return analog_pin_number;
}
