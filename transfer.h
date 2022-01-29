/*
 * transfer.h
 *
 *  Created on: Jan 8, 2022
 *      Author: nanker
 */

#ifndef TRANSFER_H_
#define TRANSFER_H_

#include <stdint.h>


void xfer(volatile uint8_t *dout,uint8_t *din,uint32_t size,uint8_t mode);
void __spi_ads8343(volatile uint8_t *dout,uint8_t *din,uint32_t size);
void __spi_ads8343(volatile uint8_t *dout,uint8_t *din,uint32_t size);

#endif /* TRANSFER_H_ */
