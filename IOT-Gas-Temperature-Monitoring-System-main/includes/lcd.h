/*
 * lcd.h
 * Header file for 16x2 LCD interface functions
 */

#ifndef _LCD_H_
#define _LCD_H_

#include "types.h"

/* Initialize LCD */
void InitLCD(void);

/* Send command to LCD */
void CmdLCD(u8 cmd);

/* Display a single character */
void CharLCD(s8 data);

/* Display a string */
void StrLCD(char *str);

/* Display integer value */
void IntLCD(s32 num);

/* Display floating point value */
void F32LCD(f32 num, u32 nDP);

/* Write custom character to CGRAM */
void WriteTOCGRAM(void);

#endif
