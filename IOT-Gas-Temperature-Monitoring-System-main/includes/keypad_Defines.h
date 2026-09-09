/*
 * keypad_Defines.h
 * Definitions for 4x4 matrix keypad
 */

#ifndef _KEYPAD_DEFINES_H_
#define _KEYPAD_DEFINES_H_

/* ---------- KEY MAPPING LUT ---------- */

// 4x4 keypad lookup table
static const char LUT[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

/* ---------- ROW PINS (P1.16 - P1.19) ---------- */

#define R0 16
#define R1 17
#define R2 18
#define R3 19

/* ---------- COLUMN PINS (P1.20 - P1.23) ---------- */

#define C0 20
#define C1 21
#define C2 22
#define C3 23

#endif

