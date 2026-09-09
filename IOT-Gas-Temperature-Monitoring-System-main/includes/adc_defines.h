/*
 * adc_defines.h
 * Definitions and macros for ADC configuration
 */

#ifndef _ADC_DEFINES_H_
#define _ADC_DEFINES_H_

/* ---------- CLOCK CONFIGURATION ---------- */

// Available crystal frequency
#define FOSC 12000000      // 12 MHz

// CPU clock (as per startup configuration)
#define CCLK (FOSC * 5)    // 60 MHz max

// Peripheral clock
#define PCLK (CCLK / 4)    // 15 MHz max

/* ---------- ADC CLOCK ---------- */

// ADC operating frequency (must be <= 4.5 MHz)
#define ADCCLK 3000000     

/* ---------- ADCR REGISTER BITS ---------- */

// Clock divider for ADC
#define CLKDIV ((PCLK / ADCCLK) - 1)

// Bit positions in ADCR register
#define CLKDIV_BITS_START 8   // Bits 8–15
#define PDN_BIT           21  // Power down bit
#define CONV_START_BIT    24  // Start conversion bit

/* ---------- ADDR REGISTER BITS ---------- */

// ADC result starts from bit 6
#define RESULT_BITS_START 6   // Bits 6–15

// Conversion complete flag
#define DONE_BIT          31  

/* ---------- PIN CONFIGURATION ---------- */

// Configure P0.27–P0.30 as ADC inputs (AIN0–AIN3)
#define AIN0_0_27    0x00400000
#define AIN1_0_28    0x01000000
#define AIN2_0_29    0x04000000
#define AIN3_0_30    0x10000000

#endif
