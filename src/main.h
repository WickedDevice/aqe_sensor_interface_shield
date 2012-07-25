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
#define CO_HEATER_POWER_ADC        6
#define CO_HEATER_FEEDBACK_ADC     3
#define HEATER_FEEDBACK_RESISTANCE 68L // ohms
#define NO2_HEATER_TARGET_POWER_MW 43L // mW
#define CO_HEATER_TARGET_POWER_MW  76L // mW

void manageHeater(uint8_t power_adc_num, uint8_t feedback_adc_num, uint32_t feedback_resistance, uint32_t target_power_mw);

#endif /* MAIN_H_ */
