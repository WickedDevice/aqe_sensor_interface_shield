/*
 * mac.h
 *
 *  Created on: Aug 15, 2012
 *      Author: vic
 */

#ifndef MAC_H_
#define MAC_H_

#include <stdint.h>

// public functions
void mac_init();
uint8_t * mac_get();

// private functions
void mac_unio_standby();
void mac_unio_start_header();
void mac_unio_sendByte(uint8_t data);
void mac_unio_readBytes(uint8_t *addr, uint16_t length);
uint8_t mac_unio_readBit();


#endif /* MAC_H_ */
