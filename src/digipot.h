/*
 * digipot.h
 *
 *  Created on: Jul 24, 2012
 *      Author: vic
 */

#ifndef DIGIPOT_H_
#define DIGIPOT_H_

#include <avr/io.h>
#define DIGIPOT_SLAVE_SELECT_DDR  DDRD
#define DIGIPOT_SLAVE_SELECT_PORT PORTD
#define DIGIPOT_SLAVE_SELECT_PIN  2

#define DIGIPOT_CMD_READ      0x0C //B00001100
#define DIGIPOT_CMD_INCREMENT 0x04 //B00000100
#define DIGIPOT_CMD_DECREMENT 0x08 //B00001000
#define DIGIPOT_ADR_WIPER0    0x00 //B00000000
#define DIGIPOT_ADR_WIPER1    0x10 //B00010000
#define DIGIPOT_ADR_VOLATILE  0x00 //B00000000
#define DIGIPOT_ADR_STATUS    0x50 //B01010000
#define DIGIPOT_WIPER0        DIGIPOT_ADR_WIPER0
#define DIGIPOT_WIPER1        DIGIPOT_ADR_WIPER1

void digipot_select_slave();
void digipot_deselect_slave();
void digipot_write(uint8_t data_byte);

void digipot_init();
void digipot_increment(uint8_t wiper_num, uint8_t n);
void digipot_decrement(uint8_t wiper_num, uint8_t n);
uint16_t digipot_read_wiper0();
uint16_t digipot_read_wiper1();
uint16_t digipot_read_status();

#endif /* DIGIPOT_H_ */
