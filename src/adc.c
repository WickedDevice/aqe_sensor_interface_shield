/*
 * adc.c
 *
 *  Created on: Jul 21, 2012
 *      Author: vic
 */
#include <stdint.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "adc.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/* this implementation follows the guidance of
 * Atmel App Note AVR125 Section 3.1 Single conversion
 * some of the code particulars are borrowed from arduino source code */
uint16_t analogRead(uint8_t channel_num){
    uint8_t high = 0, low = 0;

    // the following evaluates to ADMUX & 0xF0
    uint8_t temp = ADMUX & ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3)); // ADMUX with the MUX bits cleared

    // Set the Mux bitfield (MUX3:0) in ADC’s MUX register (ADMUX)
    // channel num should be in the range of 0 .. 8, but not checked
    // the following evaluates to channel & 0x0F
    temp |= channel_num & (_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));   // makes sure we don't affect other register bits

    // Set the Voltage Reference bitfield (REFS0) to select AVcc reference
    temp |= _BV(REFS0);

    ADMUX = temp; // write the prescribed value back to the register

    // Set the ADC Prescaler  bitfield (ADPS2:0) in ADCSRA equal to 100 to prescale system clock by 8.
    // By default, the successive approximation circuitry requires an input clock frequency between 50
    // kHz and 200 kHz to get maximum resolution, per the ATtin48 datasheet.
    // Since we're assuming running @ 8MHz, 8MHz/64 = 125kHz is in the required range of 50kHz to 200kHz
    // the following evaluates to ADCSRA & 0xF8 (clear the prescaler bits)
    temp = ADCSRA & ~(_BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2));

    // set the bits for /64 prescaler
    temp |= _BV(ADPS1) | _BV(ADPS2);

    // enable the ADC
    temp |= _BV(ADEN);

    ADCSRA = temp; // write the prescribed value back to the register

    sbi(ADCSRA, ADSC); // start the conversion

    // Wait for the  Interrupt Flag  bit (ADIF) in ADCSRA to be set, indicating that the conversion is finished
    // ADSC is cleared when the conversion finishes
    while (bit_is_set(ADCSRA, ADSC));

    // we have to read ADCL first; doing so locks both ADCL
    // and ADCH until ADCH is read.  reading ADCL second would
    // cause the results of each conversion to be discarded,
    // as ADCL and ADCH would be locked when it completed.
    low  = ADCL;
    high = ADCH;

    return (high << 8) | low;
}


