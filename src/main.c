/*
 * main.c
 *
 *  Created on: Jul 14, 2012
 *      Author: vic
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "twi.h"
#include "spi.h"
#include "adc.h"
#include "egg_bus.h"
#include "digipot.h"
#include "heater_control.h"
#include "mac.h"
#include "utility.h"
#include <math.h>
#include <limits.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//#define INCLUDE_DEBUG_REGISTERS

void onRequestService(void);
void onReceiveService(uint8_t* inBytes, int numBytes);

void setup(void);

uint8_t macaddr[6];

void main(void) __attribute__((noreturn));
void main(void) {
    uint8_t momentum[2] = {1, 1};
    int8_t last_direction[2] = {0,0};

    setup();
    sei();    // enable interrupts

    // This loop runs forever, its sole purpose is to keep the heater power constant
    // it can be interrupted at any point by a TWI event
    for (;;) {
        for(uint8_t ii = 0; ii < EGG_BUS_NUM_HOSTED_SENSORS; ii++){
            int8_t direction = heater_control_manage(ii, momentum[ii]) > 0 ? 1 : -1;

            if(direction == last_direction[ii] && direction != 0){
                momentum[ii] += 1; // change faster
            }
            else{
                momentum[ii] = 1; // reset to slow changes
            }

            if(direction != 0){
                last_direction[ii] = direction;
            }
        }

        delay_sec(3); // only change the heater voltage every three seconds or so to give it time to settle in
    }
}

// this gets called when you get an SLA+R
void onRequestService(void){
    uint8_t response[EGG_BUS_MAX_RESPONSE_LENGTH] = { 0 };
    uint8_t response_length = 4; // unless it gets overridden 4 is the default
    uint8_t sensor_index = 0;
    uint8_t sensor_field_offset = 0;
    uint16_t address = egg_bus_get_read_address(); // get the address requested in the SLA+W
    uint16_t sensor_block_relative_address = address - ((uint16_t) EGG_BUS_SENSOR_BLOCK_BASE_ADDRESS);
    uint16_t possible_values[3] = {0,0,0};
    uint32_t possible_low_side_resistances[3] = {0,0,0};
    uint8_t best_value_index = 0;
    uint32_t responseValue = 0;

    switch(address){
    case EGG_BUS_ADDRESS_SENSOR_COUNT:
        response[0] = EGG_BUS_NUM_HOSTED_SENSORS;
        response_length = 1;
        break;
    case EGG_BUS_ADDRESS_MODULE_ID:
        memcpy(response, macaddr, 6);
        response_length = 6;
        break;
    case EGG_BUS_FIRMWARE_VERSION:
        big_endian_copy_uint32_to_buffer(EGG_BUS_FIRMWARE_VERSION_NUMBER, response);
        break;
#ifdef INCLUDE_DEBUG_REGISTERS
    case EGG_BUS_DEBUG_NO2_HEATER_VOLTAGE_PLUS:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_power_voltage(0), response);
        break;
    case EGG_BUS_DEBUG_NO2_HEATER_VOLTAGE_MINUS:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_feedback_voltage(0), response);
        break;
    case EGG_BUS_DEBUG_NO2_HEATER_POWER_MW:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_power_mw(0), response);
        break;
    case EGG_BUS_DEBUG_NO2_DIGIPOT_WIPER:
        big_endian_copy_uint32_to_buffer((uint32_t) digipot_read_wiper1(), response);
        break;
    case EGG_BUS_DEBUG_CO_HEATER_VOLTAGE_PLUS:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_power_voltage(1), response);
        break;
    case EGG_BUS_DEBUG_CO_HEATER_VOLTAGE_MINUS:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_feedback_voltage(1), response);
        break;
    case EGG_BUS_DEBUG_CO_HEATER_POWER_MW:
        big_endian_copy_uint32_to_buffer(heater_control_get_heater_power_mw(1), response);
        break;
    case EGG_BUS_DEBUG_CO_DIGIPOT_WIPER:
        big_endian_copy_uint32_to_buffer((uint32_t) digipot_read_wiper0(), response);
        break;
    case EGG_BUS_DEBUG_DIGIPOT_STATUS:
        big_endian_copy_uint32_to_buffer((uint32_t) digipot_read_status(), response);
        blinkLEDs(1, POWER_LED);
        break;
#endif
    default:
        if(address >= EGG_BUS_SENSOR_BLOCK_BASE_ADDRESS){
            sensor_index = sensor_block_relative_address / ((uint16_t) EGG_BUS_SENSOR_BLOCK_SIZE);
            sensor_field_offset = sensor_block_relative_address % ((uint16_t) EGG_BUS_SENSOR_BLOCK_SIZE);
            switch(sensor_field_offset){
            case EGG_BUS_SENSOR_BLOCK_TYPE_OFFSET:
                egg_bus_get_sensor_type(sensor_index, (char *) response);
                response_length = 16;
                break;
            case EGG_BUS_SENSOR_BLOCK_UNITS_OFFSET:
                egg_bus_get_sensor_units(sensor_index, (char *) response);
                response_length = 16;
                break;
            case EGG_BUS_SENSOR_BLOCK_R0_OFFSET:
                big_endian_copy_uint32_to_buffer(egg_bus_get_r0_ohms(sensor_index), response);
                break;
            case EGG_BUS_SENSOR_BLOCK_COMPUTED_VALUE_OFFSET: //
                big_endian_copy_uint32_to_buffer((uint32_t) analogRead(egg_bus_map_to_analog_pin(sensor_index)), response);
                break;
            case EGG_BUS_SENSOR_BLOCK_UNITS_MULTIPLIER_OFFSET:
                break;
            case EGG_BUS_SENSOR_BLOCK_RAW_VALUE_OFFSET:
            case EGG_BUS_SENSOR_BLOCK_SENSOR_RESISTANCE:
                possible_low_side_resistances[0] = get_r1(sensor_index) + get_r2(sensor_index) + get_r3(sensor_index);
                possible_low_side_resistances[1] = get_r1(sensor_index) + get_r2(sensor_index);
                possible_low_side_resistances[2] = get_r1(sensor_index);

                // R2 and R3 enabled
                SENSOR_R2_ENABLE(sensor_index);
                SENSOR_R3_ENABLE(sensor_index);
                _delay_ms(20);
                possible_values[0] = analogRead(egg_bus_map_to_analog_pin(sensor_index));

                // R3 disabled
                SENSOR_R3_DISABLE(sensor_index);
                _delay_ms(20);
                possible_values[1] = analogRead(egg_bus_map_to_analog_pin(sensor_index));

                // R2 and R3 disabled
                SENSOR_R2_DISABLE(sensor_index);
                _delay_ms(20);
                possible_values[2] = analogRead(egg_bus_map_to_analog_pin(sensor_index));

                // figure out the "best value index" ... here's how this algorithm works:
                // If the ADC reading when using the R1 + R2 + R3 chain is below THRESHOLD1 use that value
                // else if the ADC reading when using the R1 + R2 chain is below THRESHOLD2 use that value
                // else use the ADC reading using the R1 chain
                if(possible_values[0] < get_r1r2r3_threshold(sensor_index)){
                    best_value_index = 0;
                }
                else if(possible_values[1] < get_r1r2_threshold(sensor_index)){
                    best_value_index = 1;
                }
                else{
                    best_value_index = 2;
                }

                if(sensor_field_offset == EGG_BUS_SENSOR_BLOCK_RAW_VALUE_OFFSET){
                    response_length = 8;
                    big_endian_copy_uint32_to_buffer((uint32_t) possible_values[best_value_index], response);
                    big_endian_copy_uint32_to_buffer((uint32_t) possible_low_side_resistances[best_value_index], response + 4 );
                }
                else{ // if sensor_field_offset == EGG_BUS_SENSOR_BLOCK_SENSOR_RESISTANCE
                    uint32_t a = (((uint32_t) possible_values[best_value_index]) * ((uint32_t) ADC_VCC_TENTH_VOLTS)); // VCC * ADC
                    uint32_t b = (1024L * ((uint32_t) get_sensor_vcc(sensor_index))); // 1024 * SENSOR_VCC
                    if(a > b){
                        responseValue = 0; // short circuit
                    }
                    else{
                        responseValue = b - a;

                        // before we multiply by a potentially large value lets find out if it's going to make us overflow and avert that if possible
                        if(possible_low_side_resistances[best_value_index] > (((uint32_t) 0xffffffff) / responseValue) ){
                            if(possible_values[best_value_index] != 0){
                                responseValue /= ((uint32_t) ADC_VCC_TENTH_VOLTS);
                                responseValue *= possible_low_side_resistances[best_value_index];
                                responseValue /= ((uint32_t) possible_values[best_value_index]);
                            }
                            else{
                                responseValue = 0xffffffff; // infinity
                            }
                        }
                        else{
                            responseValue *= possible_low_side_resistances[best_value_index];
                            if(possible_values[best_value_index] != 0){
                                responseValue /= ((uint32_t) possible_values[best_value_index]) * ((uint32_t) ADC_VCC_TENTH_VOLTS);
                            }
                            else{
                                responseValue = 0xffffffff; // infinity
                            }
                        }
                    }
                    big_endian_copy_uint32_to_buffer(responseValue, response);
                }

                break;
            }
        }
        break;
    }

    // write the value back to the master per the protocol requirements
    // the response is always four bytes, most significant byte first
    twi_transmit(response, response_length);
}

// this gets called when you get an SLA+W  then numBytes bytes, then stop
//   numBytes bytes have been buffered in inBytes by the twi library
// it seems quite critical that we not dilly-dally in this function, get in and get out ASAP
void onReceiveService(uint8_t* inBytes, int numBytes){
    POWER_LED_TOGGLE();
    switch(inBytes[0]){
    case EGG_BUS_COMMAND_READ:
        // reconstitute the read address
        egg_bus_set_read_address((((uint16_t) inBytes[1]) << 8) | inBytes[2]);
        break;
    case EGG_BUS_COMMAND_WRITE:
        // TODO: not yet implemented
        break;
    }
}

void setup(void){
    POWER_LED_INIT();
    STATUS_LED_INIT();
    POWER_LED_ON();
    delay_sec(1);

    unio_init(NANODE_MAC_DEVICE);
    unio_read(macaddr, NANODE_MAC_ADDRESS, 6);

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

    // Initialize the 2 sensor dividers as tristated inputs
    SENSOR_R2_ENABLE(0);
    SENSOR_R3_ENABLE(0);
    SENSOR_R2_ENABLE(1);
    SENSOR_R3_ENABLE(1);

    POWER_LED_OFF();

    spi_begin();
    digipot_init();

    blinkLEDs(1, STATUS_LED);
    STATUS_LED_OFF();
}

