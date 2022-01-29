/*
 * main.h
 *
 *  Created on: Jan 8, 2022
 *      Author: nanker
 */

#ifndef MAIN_H_
#define MAIN_H_
#define P9_41   (1 << 16)
#define MOSI    P9_30
#define MISO    P9_29
#define SCK     P9_31
#define ADCCS   P9_27
#define DACCS   P9_28
#define DACLD   P8_12
#define ADCBUSY P9_25
#define CS0     ADCCS
#define CS1     DACCS
#define ADC     0
#define DAC     1

// ADS8343 defines
#define DIFF_MODE   false
#define SBIT        0x80
#define A2          0x40
#define A1          0x20
#define A0          0x10
#define SGL         0x04
#define PD1         0x02
#define PD0         0x01

#define SPI_MISO    (__R30 & MISO)?1:0;
#define cs_low(x)       __R30 &= ~x##CS
#define cs_high(x)      __R30 |= x##CS;
#define sck_low()       __R30 &= ~SCK
#define sck_high()      __R30 |= SCK
#define mosi_high()     __R30 |= MOSI
#define mosi_low()      __R30 &= ~MOSI
#define dacld_high()    __R30 |= DACLD
#define dacld_low()     __R30 &= ~DACLD
#define set_mosi(x)     ((x) & 0x80)?(__R30 |= MOSI):(__R30 &= ~MOSI)
#define SPI_MODE0   0   // CPOL=0 CPHA=0
#define SPI_MODE1   1   // CPOL=0 CPHA=1
#define SPI_MODE2   2   // CPOL=1 CPHA=0
#define SPI_MODE3   3   // CPOL=1 CPHA=1

#define CPHA(x)     (x & 0x1)   // check first mode bit
#define CPOL(x)     ((x & 0x2) >> 1)   // check second mode bit
#endif /* MAIN_H_ */
