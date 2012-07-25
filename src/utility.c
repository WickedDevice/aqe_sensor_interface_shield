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
    for(uint8_t i = 0; i < 2 * n; i++ ){
        if(which_led == 0) STATUS_LED_TOGGLE();
        else POWER_LED_TOGGLE();
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
