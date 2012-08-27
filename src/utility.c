/*
 * utility.c
 *
 *  Created on: Jul 24, 2012
 *      Author: vic
 */

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "utility.h"


// just a visual feedback mechanism
void blinkLEDs(uint8_t n, uint8_t which_led){
    for(uint8_t i = 0; i < n; i++ ){
        if(which_led == 0) STATUS_LED_ON();
        else POWER_LED_ON();
        _delay_ms(50);
        if(which_led == 0) STATUS_LED_OFF();
        else POWER_LED_OFF();

        _delay_ms(200);
    }
}

void delay_sec(uint8_t n){
    for(uint8_t i = 0; i < n; i++){
        _delay_ms(1000);
    }
}

uint16_t byte2uint16(uint8_t high_byte, uint8_t low_byte){
  return (uint16_t)high_byte<<8 | (uint16_t)low_byte;
}

uint8_t uint16_high_byte(uint16_t uint16){
  return (uint8_t)(uint16>>8);
}

uint8_t uint16_low_byte(uint16_t uint16){
  return (uint8_t)(uint16 & 0x00FF);
}

void big_endian_copy_uint32_to_buffer(uint32_t value, uint8_t * buffer){
    int8_t ii = 0;
    for(ii = 3; ii >= 0; ii--){
        *buffer++ = (value >> (8 * ii)) & 0xff;
    }
}

uint16_t get_r1(uint8_t sensor_index){
    return sensor_index == 0 ? NO2_SENSOR_R1 : CO_SENSOR_R1;
}

uint16_t get_r2(uint8_t sensor_index){
    return sensor_index == 0 ? NO2_SENSOR_R2 : CO_SENSOR_R2;
}

uint16_t get_r3(uint8_t sensor_index){
    return sensor_index == 0 ? NO2_SENSOR_R3 : CO_SENSOR_R3;
}
