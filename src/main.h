/*
 * main.h
 *
 *  Created on: Jul 14, 2012
 *      Author: vic
 */

#ifndef MAIN_H_
#define MAIN_H_

#define NO2_HEATER_POWER_ADC       7
#define NO2_HEATER_FEEDBACK_ADC    1
#define NO2_HEATER_FEEDBACK_RESISTANCE 68L // ohms
#define NO2_HEATER_TARGET_POWER_MW 43L // mW

#define CO_HEATER_POWER_ADC        6
#define CO_HEATER_FEEDBACK_ADC     3
#define CO_HEATER_FEEDBACK_RESISTANCE 68L // ohms
#define CO_HEATER_TARGET_POWER_MW  76L // mW

typedef struct{
    uint32_t heater_feedback_resistance;
    uint32_t heater_target_power_mw;
    uint8_t  heater_power_adc;
    uint8_t  heater_feedback_adc;
    uint8_t  digipot_wiper;
} sensor_config_t;

int8_t manageHeater(uint8_t sensor_index, uint8_t momentum);

#endif /* MAIN_H_ */
