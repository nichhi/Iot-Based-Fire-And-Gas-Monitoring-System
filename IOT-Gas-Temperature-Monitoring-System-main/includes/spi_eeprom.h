/*
 * spi_eeprom.h
 * Header file for SPI EEPROM operations
 */

#ifndef _SPI_EEPROM_H_
#define _SPI_EEPROM_H_

#include "types.h"

/* ---------- BASIC COMMAND ---------- */

// Send command to EEPROM
void Cmd(u8 cmdByte);

/* ---------- BYTE OPERATIONS ---------- */

// Write one byte to EEPROM
void ByteWrite(u16 wBuffAddr, u8 wByte);

// Read one byte from EEPROM
u8 ByteRead(u16 rBuffAddr);

/* ---------- INTEGER OPERATIONS ---------- */

// Write integer (2 bytes) to EEPROM
void EEPROM_WriteInt(u16 addr, int value);

// Read integer (2 bytes) from EEPROM
int EEPROM_ReadInt(u16 addr);

/* ---------- OPTIONAL SETPOINT FUNCTIONS ---------- */
// void Save_SetPoint(u8 sp);
// u8 Load_SetPoint(void);

#endif
