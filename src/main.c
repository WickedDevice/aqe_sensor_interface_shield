/*
 * main.c
 *
 *  Created on: Jul 14, 2012
 *      Author: vic
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "main.h"
#include "twi.h"

/* TWI constants and prototypes */
#define TWI_SLAVE_ADDRESS               3    // must be less than 127
#define TWI_BUFFER_SIZE                 8
#define TWI_GET_NUM_SENSORS_ATTACHED    0x00 // no parameters
#define TWI_GET_RAW_SENSOR_VALUE        0x11 // parameter = sensor index
#define TWI_GET_CALUCLATED_SENSOR_VALUE 0x22 // parameter = sensor index
void onRequestService(void);
void onReceiveService(uint8_t* inBytes, int numBytes);

/* Utility constants and prototypes */
void blinkLEDs(uint8_t n);

void main(void) __attribute__((noreturn));
void main(void) {

    POWER_LED_INIT();
    STATUS_LED_INIT();
    POWER_LED_ON();
    _delay_ms(1000);

    // TWI Initialize
    twi_setAddress(TWI_SLAVE_ADDRESS);
    twi_attachSlaveTxEvent(onRequestService);
    twi_attachSlaveRxEvent(onReceiveService);
    twi_init();

    POWER_LED_OFF();

    sei();
    blinkLEDs(2);

    // This loop runs forever, its sole purpose is to keep the heater power constant
    // it can be interrupted at any point by a TWI event
    for (;;) {
        // read the voltage being output by the adjustable regulator


        // read the voltage on the low side of the heater


        // calculate the power being dissipated in the heater


        // adjust the voltage being output by the adjustable regulator by
        // changing increasing or decreasing the variable feedback resistance


    }
}

// this gets called when you get an SLA+R
void onRequestService(void){
    blinkLEDs(1); // good times

    // read the analog sensor that has been previously commanded

    // write the value back to the master per the protocol requirements

}

// this gets called when you get an SLA+W  then numBytes bytes, then stop
//   numBytes bytes have been buffered in inBytes by the twi library
void onReceiveService(uint8_t* inBytes, int numBytes){
    blinkLEDs(2); // good times
    // currently nothing to do here

}

// just a visual feedback mechanism
void blinkLEDs(uint8_t n){
    for(uint8_t i = 0; i < n; i++ ){
        STATUS_LED_TOGGLE();
        _delay_ms(200);
    }
}
