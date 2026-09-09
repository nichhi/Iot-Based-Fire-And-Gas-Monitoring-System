/*
 * lcd_defines.h
 * LCD command definitions for 16x2 display
 */

#ifndef _LCD_DEFINES_H_
#define _LCD_DEFINES_H_

/* ---------- LCD CURSOR POSITIONS ---------- */

// Move cursor to line 1, position 0
#define GOTO_LINE1_POS0   0x80

// Move cursor to line 2, position 0
#define GOTO_LINE2_POS0   0xC0

/* ---------- LCD CONTROL COMMANDS ---------- */

// Display ON, Cursor OFF
#define DISP_ON_CUR_OFF   0x0C

// Clear LCD display
#define CLEAR_LCD         0x01

#endif
