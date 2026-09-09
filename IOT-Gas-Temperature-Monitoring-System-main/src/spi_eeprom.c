//spi_eeprom.c

#include <LPC21xx.h>
#include "types.h"
#include "spi.h"
#include "spi_eeprom_defines.h"
#include "delay.h"
#include "spi_eeprom.h"
#include "spi_defines.h"

#define SETPOINT_ADDR 0x0000   // EEPROM address for storing setpoint

/* ---------- SEND COMMAND TO EEPROM ---------- */
void Cmd(u8 cmdByte)
{
	// Select EEPROM (CS LOW)
	IOCLR0 = 1<<SS0_PIN;

	// Send command byte via SPI
	spi0(cmdByte);

	// Deselect EEPROM (CS HIGH)
	IOSET0 = 1<<SS0_PIN;
}

/* ---------- WRITE ONE BYTE TO EEPROM ---------- */
void ByteWrite(u16 wBuffAddr, u8 wByte)
{
	// Enable write operation (WREN command)
	Cmd(WREN);

	// Select EEPROM
	IOCLR0 = 1<<SS0_PIN;

	// Send WRITE command
	spi0(WRITE);

	// Send address (MSB first)
	spi0(wBuffAddr >> 8);

	// Send address (LSB)
	spi0(wBuffAddr);

	// Send data byte to be stored
	spi0(wByte);

	// Deselect EEPROM
	IOSET0 = 1<<SS0_PIN;

	// Wait for internal write cycle to complete
	delay_ms(5);

	// Disable write (WRDI command)
	Cmd(WRDI);
}

/* ---------- READ ONE BYTE FROM EEPROM ---------- */
u8 ByteRead(u16 rBuffAddr)
{
	u8 rByte;

	// Select EEPROM
	IOCLR0 = 1<<SS0_PIN;

	// Send READ command
	spi0(READ);

	// Send address (MSB)
	spi0(rBuffAddr >> 8);

	// Send address (LSB)
	spi0(rBuffAddr);

	// Send dummy byte to receive data
	rByte = spi0(0x00);

	// Deselect EEPROM
	IOSET0 = 1<<SS0_PIN;

	return rByte;
}


