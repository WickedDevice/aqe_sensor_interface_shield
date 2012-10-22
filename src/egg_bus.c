/*
 * egg_bus.c
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "egg_bus.h"
#include "utility.h"

static uint16_t egg_bus_read_address = 0;
static uint8_t egg_bus_sensor_mapping_table[] = {
        0, // index 0 [NO2] is on ADC0
        2, // index 1 [CO] is on  ADC2
};

char egg_bus_sensor_type_0[] PROGMEM = "NO2";
char egg_bus_sensor_type_1[] PROGMEM = "CO";
PGM_P egg_bus_sensor_types[] PROGMEM = {
        egg_bus_sensor_type_0,
        egg_bus_sensor_type_1
};

char egg_bus_sensor_units_0[] PROGMEM = "ppb";
char egg_bus_sensor_units_1[] PROGMEM = "ppb";
PGM_P egg_bus_sensor_units[] PROGMEM = {
        egg_bus_sensor_units_0,
        egg_bus_sensor_units_1
};

uint32_t EEMEM egg_bus_sensor_r0[EGG_BUS_NUM_HOSTED_SENSORS]  = { 2200, 750000 }; // values in ohms

uint16_t egg_bus_get_read_address(){
    return egg_bus_read_address;
}

void egg_bus_set_read_address(uint16_t read_address){
    egg_bus_read_address = read_address;
}

uint8_t egg_bus_map_to_analog_pin(uint8_t sensor_index){
    uint8_t analog_pin_number = 0;
    if(sensor_index < EGG_BUS_NUM_HOSTED_SENSORS){
        analog_pin_number = egg_bus_sensor_mapping_table[sensor_index];
    }
    return analog_pin_number;
}

void egg_bus_get_sensor_type(uint8_t sensor_index, char * target_buffer){
    strcpy_P(target_buffer, (PGM_P)pgm_read_word(&(egg_bus_sensor_types[sensor_index])));
}

void egg_bus_get_sensor_units(uint8_t sensor_index, char * target_buffer){
    strcpy_P(target_buffer, (PGM_P)pgm_read_word(&(egg_bus_sensor_units[sensor_index])));
}

uint32_t egg_bus_get_r0_ohms(uint8_t sensor_index){
    uint32_t ret_value = 0;
    eeprom_read_block (( void *) &ret_value , ( const void *) (&egg_bus_sensor_r0[sensor_index]) , 4) ;
    return ret_value;
}
