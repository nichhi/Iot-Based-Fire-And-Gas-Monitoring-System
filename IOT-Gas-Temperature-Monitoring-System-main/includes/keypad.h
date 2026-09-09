/*
 * keypad.h
 * Header file for 4x4 keypad interface
 */

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

/* Initialize keypad GPIO pins */
void KeyadInit(void);

/* Check column status (key press detection) */
int ColStat(void);

/* Read a single key value from keypad */
char ReadKeyVal(void);

/* Read multi-digit number from keypad */
int Readnum(void);

#endif

