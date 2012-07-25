/*
 * digipot.c
 *
 *  Created on: Jul 24, 2012
 *      Author: vic
 */

#include <avr/io.h>
#include "digipot.h"
#include "spi.h"
#include "utility.h"

void digipot_select_slave(){
    DIGIPOT_SLAVE_SELECT_PORT &= ~_BV(DIGIPOT_SLAVE_SELECT_PIN);
}

void digipot_deselect_slave(){
    DIGIPOT_SLAVE_SELECT_PORT |= _BV(DIGIPOT_SLAVE_SELECT_PIN);
}

void digipot_init(){
    // set the slave select pin to an output high
    DIGIPOT_SLAVE_SELECT_DDR |= _BV(DIGIPOT_SLAVE_SELECT_PIN);
    DIGIPOT_SLAVE_SELECT_PORT |= _BV(DIGIPOT_SLAVE_SELECT_PIN);
}

void digipot_increment(uint8_t wiper_num, uint8_t n){
    uint8_t cmd = DIGIPOT_CMD_INCREMENT;
    if(wiper_num == DIGIPOT_ADR_WIPER1){
        cmd |= DIGIPOT_ADR_WIPER1;
    }

    for(uint8_t i = 0; i < n; i++){
        digipot_write(cmd);
    }
}

void digipot_decrement(uint8_t wiper_num, uint8_t n){
    uint8_t cmd = DIGIPOT_CMD_DECREMENT;
    if(wiper_num == DIGIPOT_ADR_WIPER1){
        cmd |= DIGIPOT_ADR_WIPER1;
    }

    for(uint8_t i = 0; i < n; i++){
        digipot_write(cmd);
    }
}

void digipot_write(uint8_t cmd_byte)
{
  digipot_select_slave();
  spi_transfer(cmd_byte);
  digipot_deselect_slave();
}
