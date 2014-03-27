/*
 * interpolation.c
 *
 *  Created on: Oct 21, 2012
 *      Author: vic
 */

#include "interpolation.h"
#include "egg_bus.h"
#include "utility.h"
#include <float.h>

#define INTERPOLATION_X_INDEX 0
#define INTERPOLATION_Y_INDEX 1
#define INTERPOLATION_TERMINATOR 0xff

// these are the conversion factors required to turn into floating point values (multiply table values by these)
#ifdef HW_VERSION_1_5
const float x_scaler[EGG_BUS_NUM_HOSTED_SENSORS] = {0.4f, 0.003f};
const float y_scaler[EGG_BUS_NUM_HOSTED_SENSORS] = {1.7f, 165.0f};
#endif
#ifdef HW_VERSION_1_6
const float x_scaler[EGG_BUS_NUM_HOSTED_SENSORS] = {2.65f, 0.003f};
const float y_scaler[EGG_BUS_NUM_HOSTED_SENSORS] = {1.6f, 165.0f};
#endif
const float independent_scaler[EGG_BUS_NUM_HOSTED_SENSORS] = {0.001f, 0.001f};
const uint32_t independent_scaler_inverse[EGG_BUS_NUM_HOSTED_SENSORS] = { 1000L, 1000L };

// get_x_or_get_y = 0 returns x value from table, get_x_or_get_y = 1 returns y value from table
uint8_t getTableValue(uint8_t sensor_index, uint8_t table_index, uint8_t get_x_or_get_y){

#ifdef HW_VERSION_1_5
    // the values MUST be provided in ascending order of x-value
    const uint8_t no2_ppb[][2] = {
            {0,0},
            {62,117},
            {75,131},
            {101,152},
            {149,188},
            {174,204},
            {199,219},
            {223,233},
            {247,246},
            {INTERPOLATION_TERMINATOR, INTERPOLATION_TERMINATOR}
    };
#endif

#ifdef HW_VERSION_1_6
    // the values MUST be provided in ascending order of x-value
    const uint8_t no2_ppb[][2] = {
            {0,0},
            {1,7},
            {2,15},
            {3,22},
            {4,30},
            {5,35},
            {7,42},
            {9,49},
            {16,69},
            {22,79},
            {28,90},
            {38,105},
            {52,120},
            {73,142},
            {106,169},
            {170,209},
            {251,249},
            {INTERPOLATION_TERMINATOR, INTERPOLATION_TERMINATOR}
    };
#endif

    const uint8_t co_ppb[][2] = {
            {0,0},
            {134,250},
            {168,125},
            {202,49},
            {232,12},
            {241,6},
            {INTERPOLATION_TERMINATOR, INTERPOLATION_TERMINATOR}
    };

    // sensor index 0 is the NO2 sensor
    uint8_t return_value = 0;
    if(sensor_index == 0){
        return_value = no2_ppb[table_index][get_x_or_get_y];
    }
    else{  // sensor index 1 is for CO
        return_value = co_ppb[table_index][get_x_or_get_y];
    }

    return return_value;
}

uint8_t * get_p_x_scaler(uint8_t sensor_index){
    return (uint8_t *) &(x_scaler[sensor_index]);
}

uint8_t * get_p_y_scaler(uint8_t sensor_index){
    return (uint8_t *) &(y_scaler[sensor_index]);
}

uint8_t * get_p_independent_scaler(uint8_t sensor_index){
    return (uint8_t *) &(independent_scaler[sensor_index]);
}

uint32_t get_independent_scaler_inverse(uint8_t sensor_index){
    return independent_scaler_inverse[sensor_index];
}
