/*
 * interpolation.h
 *
 *  Created on: Oct 21, 2012
 *      Author: vic
 */

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <stdint.h>

uint8_t getTableValue(uint8_t sensor_index, uint8_t table_index, uint8_t get_x_or_get_y);
uint8_t * get_p_x_scaler(uint8_t sensor_index);
uint8_t * get_p_y_scaler(uint8_t sensor_index);
uint8_t * get_p_independent_scaler(uint8_t sensor_index);
uint32_t get_independent_scaler_inverse(uint8_t sensor_index);

#endif /* INTERPOLATION_H_ */
