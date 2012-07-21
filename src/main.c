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
#include "adc.h"
#include "egg_bus.h"

/* TWI constants and prototypes */
#define TWI_SLAVE_ADDRESS               3    // must be less than 127
#define TWI_BUFFER_SIZE                 8
#define TWI_GET_NUM_SENSORS_ATTACHED    0x00 // no parameters
#define TWI_GET_RAW_SENSOR_VALUE        0x11 // parameter = sensor index
#define TWI_GET_CALUCLATED_SENSOR_VALUE 0x22 // parameter = sensor index
void onRequestService(void);
void onReceiveService(uint8_t* inBytes, int numBytes);

/* Utility constants and prototypes */
void blinkLEDs(uint8_t n, uint8_t which_led);

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

    // enable the adjustable regulators
    NO2_HEATER_INIT();
    CO_HEATER_INIT();
    ENABLE_NO2_HEATER();
    ENABLE_CO_HEATER();

    POWER_LED_OFF();

    sei();
    blinkLEDs(2, 0);

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
    uint8_t response[4] = {0,0,0,0};
    uint16_t analog_value = 0;

    //_delay_ms(5000);
    switch(egg_bus_get_command_received()){
    case EGG_BUS_COMMAND_SENSOR_COUNT:
        blinkLEDs(2, 0); // good times
        break;
    case EGG_BUS_COMMAND_GET_RAW_VALUE:
    case EGG_BUS_COMMAND_GET_CALCULATED_VALUE:
        blinkLEDs(2, 1); // good times
        break;
    }


    switch(egg_bus_get_command_received()){
    case EGG_BUS_COMMAND_SENSOR_COUNT:
        response[3] = EGG_BUS_NUM_HOSTED_SENSORS; // this unit supports two sensors
        break;
    case EGG_BUS_COMMAND_GET_RAW_VALUE:
    case EGG_BUS_COMMAND_GET_CALCULATED_VALUE:
        // read the analog sensor that has been previously commanded
        analog_value = analogRead(egg_bus_map_to_analog_pin(egg_bus_get_sensor_index_requested()));
        response[2] = analog_value >> 8;
        response[3] = analog_value & 0xff;
        break;
    }

    // write the value back to the master per the protocol requirements
    // the response is always four bytes, most significant byte first
    twi_transmit(response, 4);
}

// this gets called when you get an SLA+W  then numBytes bytes, then stop
//   numBytes bytes have been buffered in inBytes by the twi library
void onReceiveService(uint8_t* inBytes, int numBytes){
    //blinkLEDs(2, 1); // good times
    // numBytes should always be two... per the protocol
    egg_bus_set_command_received(inBytes[0]);

    // only implement cases of commands with parameters here
    switch(inBytes[0]){
    case EGG_BUS_COMMAND_SENSOR_COUNT:
    case EGG_BUS_COMMAND_GET_CALCULATED_VALUE:
        egg_bus_set_sensor_index_requested(inBytes[1]);
        break;
    }
}

// just a visual feedback mechanism
void blinkLEDs(uint8_t n, uint8_t which_led){
    for(uint8_t i = 0; i < 2 * n; i++ ){
        if(which_led == 0) STATUS_LED_TOGGLE();
        else POWER_LED_TOGGLE();
        _delay_ms(200);
    }
}
