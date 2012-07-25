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
