/*
 * heater_control.c
 *
 *  Created on: Aug 1, 2012
 *      Author: vic
 */

#include <stdint.h>
#include "heater_control.h"
#include "main.h"
#include "egg_bus.h"
#include "adc.h"
#include "digipot.h"
#include "utility.h"

/* this table stores the mapping of sensors to support hardware and associated configuration data */
static const sensor_config_t sensor_config[EGG_BUS_NUM_HOSTED_SENSORS] = {
        {NO2_HEATER_FEEDBACK_RESISTANCE, NO2_HEATER_TARGET_POWER_MW, NO2_HEATER_POWER_ADC, NO2_HEATER_FEEDBACK_ADC, DIGIPOT_WIPER1},
        {CO_HEATER_FEEDBACK_RESISTANCE, CO_HEATER_TARGET_POWER_MW, CO_HEATER_POWER_ADC, CO_HEATER_FEEDBACK_ADC, DIGIPOT_WIPER0}
};

// returns -1 if the calculated power required a decrement
// returns  0 if no adjustment was needed
// returns +1 if the calculated power required an increment
int32_t heater_control_manage(uint8_t sensor_index, uint8_t momentum){

    sensor_config_t * scfg = (sensor_config_t *) &(sensor_config[sensor_index]);
    uint32_t target_power_mw = scfg->heater_target_power_mw;
    uint8_t  digipot_wiper_num = scfg->digipot_wiper;

    uint32_t heater_power_mw = heater_control_get_heater_power_mw(sensor_index);



    // adjust the voltage being output by the adjustable regulator by
    // changing increasing or decreasing the variable feedback resistance
    if(heater_power_mw > target_power_mw){
        // cool down a bit
        digipot_increment(digipot_wiper_num, momentum);
    }
    else if(heater_power_mw < target_power_mw){
        // heat up a bit
        digipot_decrement(digipot_wiper_num, momentum);
    }

    return ((int32_t) target_power_mw - (int32_t) heater_power_mw);
}

uint16_t heater_control_get_heater_power_voltage(uint8_t sensor_index){
    sensor_config_t * scfg = (sensor_config_t *) &(sensor_config[sensor_index]);
    uint8_t power_adc_num = scfg->heater_power_adc;
    return analogRead(power_adc_num);
}

uint16_t heater_control_get_heater_feedback_voltage(uint8_t sensor_index){
    sensor_config_t * scfg = (sensor_config_t *) &(sensor_config[sensor_index]);
    uint8_t feedback_adc_num = scfg->heater_feedback_adc;
    return analogRead(feedback_adc_num);
}

uint32_t heater_control_get_heater_power_mw(uint8_t sensor_index){
    sensor_config_t * scfg = (sensor_config_t *) &(sensor_config[sensor_index]);
    uint32_t feedback_resistance = scfg->heater_feedback_resistance;

    uint16_t heater_power_voltage = heater_control_get_heater_power_voltage(sensor_index);
    uint16_t heater_feedback_voltage = heater_control_get_heater_feedback_voltage(sensor_index);
    uint32_t heater_power_mw = 0;

    // calculate the power being dissipated in the heater, integer math is fun!
    heater_power_mw = (1000L * ((((uint32_t)(heater_power_voltage - heater_feedback_voltage)) * (uint32_t) heater_feedback_voltage))) / feedback_resistance;
    // the "voltages" in this equation are actually adc counts. To get to voltage we need to multiply by 5V and divide 1024 counts (twice)
    heater_power_mw *= 5L * 5L;
    heater_power_mw /= 1024L * 1024L;
    // now we have an integer value that is actually in units of milliWatts

    return heater_power_mw;

}
