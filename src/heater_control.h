/*
 * heater_control.h
 *
 *  Created on: Aug 1, 2012
 *      Author: vic
 */

#ifndef HEATER_CONTROL_H_
#define HEATER_CONTROL_H_

#include <stdint.h>

typedef struct{
    uint32_t heater_feedback_resistance;
    uint32_t heater_target_power_mw;
    uint8_t  heater_power_adc;
    uint8_t  heater_feedback_adc;
    uint8_t  digipot_wiper;
} sensor_config_t;

int8_t heater_control_manage(uint8_t sensor_index, uint8_t momentum);
uint16_t heater_control_get_heater_power_voltage(uint8_t sensor_index);
uint16_t heater_control_get_heater_feedback_voltage(uint8_t sensor_index);
uint32_t heater_control_get_heater_power_mw(uint8_t sensor_index);
uint32_t heater_control_get_heater_power_mw(uint8_t sensor_index);

#endif /* HEATER_CONTROL_H_ */
