/*
 * adc.h
 * Header file for ADC functions
 */

#ifndef _ADC_H_
#define _ADC_H_

#include "types.h"

/* Initialize ADC */
void Init_ADC(void);

/* Read ADC value from channel */
void Read_ADC(u32 chNo, u32 *dVal, f32 *eAR);

#endif
