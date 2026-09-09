/*
 * lm35.h
 * Header file for LM35 temperature sensor functions
 */

#ifndef _LM35_H_
#define _LM35_H_

#include "types.h"

/* 
 * Reads temperature from LM35 sensor
 * degT   ? pointer to store temperature value
 * choice ? 'C' for Celsius, 'F' for Fahrenheit
 */
void Read_LM35(f32 *degT, u8 choice);

#endif
