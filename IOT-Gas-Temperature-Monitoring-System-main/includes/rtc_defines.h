/*
 * rtc_defines.h
 * Definitions and macros for RTC configuration
 */

#ifndef _RTC_DEFINES_H_
#define _RTC_DEFINES_H_

/* ---------- CLOCK CONFIGURATION ---------- */

// External crystal frequency
#define FOSC 12000000      // 12 MHz

// CPU clock frequency
#define CCLK (5 * FOSC)    // 60 MHz

// Peripheral clock frequency
#define PCLK (CCLK / 4)    // 15 MHz

/* ---------- RTC PRESCALER VALUES ---------- */

// Used to generate 1-second tick from 32.768 kHz clock
#define PREINT_VAL  ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK - (PREINT_VAL + 1) * 32768)

/* ---------- CCR REGISTER BITS ---------- */

// Enable RTC
#define RTC_ENABLE  (1 << 0)

// Reset RTC
#define RTC_RESET   (1 << 1)

// Select clock source
#define RTC_CLKSRC  (1 << 4)

/* ---------- CONTROLLER TYPE ---------- */

// Target MCU definition
#define CPU_LPC2148

#endif
