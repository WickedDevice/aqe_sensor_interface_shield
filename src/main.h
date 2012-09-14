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
#define NO2_HEATER_FEEDBACK_RESISTANCE 10L // ohms
#define NO2_HEATER_TARGET_POWER_MW 80L //43L // mW

#define CO_HEATER_POWER_ADC        6
#define CO_HEATER_FEEDBACK_ADC     3
#define CO_HEATER_FEEDBACK_RESISTANCE 10L // ohms
#define CO_HEATER_TARGET_POWER_MW  76L // mW

uint16_t averageADC(uint8_t sensor_index);

#endif /* MAIN_H_ */
