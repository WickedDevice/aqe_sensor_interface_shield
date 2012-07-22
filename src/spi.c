/*
 * spi.c
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */

#include <inttypes.h>
#include <avr/io.h>
#include "spi.h"

uint8_t spi_transfer(uint8_t _data) {
  SPDR = _data;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

void spi_begin() {
  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).

  //SPI is on PORTB 2,3,5 on the ATtiny48
  DDRB  |= _BV(2) | _BV(3) | _BV(5);    // turn SCK, MOSI, and SS to outputs
  PORTB &= ~(_BV(2) | _BV(3) | _BV(5)); // set SCK, MOSI, and SS to output low

  // Warning: if the SS pin ever becomes a LOW INPUT then SPI
  // automatically switches to Slave, so the data direction of
  // the SS pin MUST be kept as OUTPUT.
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}

void spi_end() {
  SPCR &= ~_BV(SPE);
}

void spi_setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == LSBFIRST) {
    SPCR |= _BV(DORD);
  }
  else {
    SPCR &= ~(_BV(DORD));
  }
}

void spi_setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

void spi_setClockDivider(uint8_t rate)
{
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >> 2) & SPI_2XCLOCK_MASK);
}
