/*
 * spi_defines.h
 * Definitions and macros for SPI configuration
 */

#ifndef _SPI_DEFINES_H_
#define _SPI_DEFINES_H_

/* ---------- CLOCK CONFIGURATION ---------- */

#define FOSC 12000000        // 12 MHz crystal
#define CCLK (FOSC * 5)      // CPU clock = 60 MHz
#define PCLK (CCLK / 4)      // Peripheral clock = 15 MHz

/* ---------- SPI CONTROL REGISTER (S0SPCR) BITS ---------- */

// Clock Phase
#define CPHA_BIT 3

// Clock Polarity
#define CPOL_BIT 4

// Master mode select
#define MSTR_BIT 5

/* ---------- SPI STATUS REGISTER (S0SPSR) ---------- */

// SPI transfer complete flag
#define SPIF_BIT 7

/* ---------- SPI PIN DEFINITIONS ---------- */

// SPI0 pins (PINSEL0 configuration)
#define SCK0_PIN   0x00000100   // P0.4 ? SCK0
#define MISO0_PIN  0x00000400   // P0.5 ? MISO0
#define MOSI0_PIN  0x00001000   // P0.6 ? MOSI0

// Slave Select (GPIO)
#define SS0_PIN    7            // P0.7 used as CS/SS

#endif
