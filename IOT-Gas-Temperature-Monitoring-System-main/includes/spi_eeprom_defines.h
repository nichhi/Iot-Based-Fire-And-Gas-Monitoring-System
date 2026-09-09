/*
 * spi_eeprom_defines.h
 * Command definitions for SPI EEPROM
 */

#ifndef _SPI_EEPROM_DEFINES_H_
#define _SPI_EEPROM_DEFINES_H_

/* ---------- EEPROM COMMANDS ---------- */

// Write data to EEPROM
#define WRITE   0x02

// Read data from EEPROM
#define READ    0x03

// Disable write operation
#define WRDI    0x04

// Enable write operation
#define WREN    0x06

// Add more commands if needed

#endif
