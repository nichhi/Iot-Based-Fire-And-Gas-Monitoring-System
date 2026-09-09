/*
 * spi.h
 * Header file for SPI communication functions
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "types.h"

/* Initialize SPI0 peripheral */
void Init_SPI0(void);

/* 
 * SPI data transfer function
 * Sends one byte and returns received byte
 */
u8 spi0(u8 data);

#endif
