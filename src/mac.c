/*
 * mac.c
 *
 *  Created on: Aug 15, 2012
 *      Author: vic
 */

/***********************************************************************
 * Adapted from NanodeMAC
 * Rufus Cable, June 2011 (threebytesfull)
 *
 * Library version created by Andrew Lindsay for use with Nanode and
 * EtherShield Library at https://github.com/thiseldo/EtherShield
 *
 * Based on sample code to read the MAC address from the 11AA02E48 on the
 * back of the Nanode V5 board.
 *
 * This code is hacky and basic - it doesn't check for bus errors
 * and will probably fail horribly if it's interrupted. It's best
 * run in setup() - fetch the MAC address once and keep it. After
 * the address is fetched, it puts the chip back in standby mode
 * in which it apparently only consumes 1uA.
 *
 * Feel free to reuse this code - suggestions for improvement are
 * welcome! :)
 *
 * BITS    7   6   5   4   3   2   1   0
 * PORTD = D7  D6  D5  D4  D3  D2  D1  D0
 * PORTB = -   -   D13 D12 D11 D10 D9  D8
 *
 * Nanode has UNI/O SCIO on DIG7
 *
 ***********************************************************************/

#include "mac.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#define D7_ON  (1<<7)
#define D7_OFF (~D7_ON)

#define SCIO_HIGH PORTD |= D7_ON
#define SCIO_LOW  PORTD &= D7_OFF

#define SCIO_OUTPUT DDRD |= D7_ON
#define SCIO_INPUT  DDRD &= D7_OFF

#define SCIO_READ ((PIND & D7_ON) != 0)

#define WAIT_QUARTER_BIT _delay_us(9);
#define WAIT_HALF_BIT _delay_us(20);

#define NOP PORTD &= 0xff

// Fixed Timings
// standby pulse time (600us+)
#define UNIO_TSTBY_US 600
// start header setup time (10us+)
#define UNIO_TSS_US 10
// start header low pulse (5us+)
#define UNIO_THDR_US 6

// SCIO Manipulation macros
#define BIT0 SCIO_HIGH;WAIT_HALF_BIT;SCIO_LOW;WAIT_HALF_BIT;
#define BIT1 SCIO_LOW;WAIT_HALF_BIT;SCIO_HIGH;WAIT_HALF_BIT;

static uint8_t _mac_address[6] = {1,2,3,4,5,6};

void mac_unio_standby() {

  SCIO_OUTPUT;
  SCIO_HIGH;
  _delay_us(UNIO_TSTBY_US);
}

void mac_unio_start_header() {
  SCIO_LOW;
  _delay_us(UNIO_THDR_US);
  mac_unio_sendByte(0x55);
}

void mac_unio_sendByte(uint8_t data) {

  SCIO_OUTPUT;
  for (int i=0; i<8; i++) {
    if (data & 0x80) {
      BIT1;
    } else {
      BIT0;
    }
    data <<= 1;
  }
  // MAK
  BIT1;
  // SAK?
  //bool sak = mac_unio_readBit();
  mac_unio_readBit();
}

void mac_unio_readBytes(uint8_t *addr, uint16_t length) {
  for (int i=0; i<length; i++) {

    uint8_t data = 0;
    for (int b=0; b<8; b++) {
      data = (data << 1) | (mac_unio_readBit() ? 1 : 0);
    }
    SCIO_OUTPUT;
    if (i==length-1) {
      BIT0; // NoMAK
    } else {
      BIT1; // MAK
    }
    //bool sak = mac_unio_readBit();
    mac_unio_readBit();
    addr[i] = data;
  }
}

 uint8_t mac_unio_readBit()
{
  SCIO_INPUT;
  WAIT_QUARTER_BIT;
  uint8_t value1 = SCIO_READ;
  WAIT_HALF_BIT;
  uint8_t value2 = SCIO_READ;
  WAIT_QUARTER_BIT;
  return ((value2 == 1) && (value1 == 0) ? 1 : 0);
}

void mac_init(){

  // Turn off Interrupts while we read the mac address
  cli();

  // standby
  mac_unio_standby();

  // start header
  mac_unio_start_header();

  // address A0
  mac_unio_sendByte(0xA0);
  // 0x3 READ
  mac_unio_sendByte(0x03);
  // word address MSB 0x00
  mac_unio_sendByte(0x00);
  // word address LSB 0xFA
  mac_unio_sendByte(0xFA);

  // read 6 bytes into array
  mac_unio_readBytes(_mac_address, 6);

  // back to standby
  mac_unio_standby();

  // Re-enable interrupts
  sei();

}

uint8_t * mac_get(){
    return _mac_address;
}
