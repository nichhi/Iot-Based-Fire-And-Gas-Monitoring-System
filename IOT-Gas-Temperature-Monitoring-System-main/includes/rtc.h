/*
 * rtc.h
 * Header file for Real-Time Clock (RTC) functions
 */

#ifndef _RTC_H_
#define _RTC_H_

#include "types.h"

/* ---------- INITIALIZATION ---------- */

// Initialize RTC
void RTC_Init(void);

/* ---------- TIME FUNCTIONS ---------- */

// Get current time (hour, minute, second)
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second);

// Display time on LCD
void DisplayRTCTime(u32 hour, u32 minute, u32 second);

// Set RTC time
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second);

/* ---------- DATE FUNCTIONS ---------- */

// Get current date (day, month, year)
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year);

// Display date on LCD
void DisplayRTCDate(u32 date, u32 month, u32 year);

// Set RTC date
void SetRTCDateInfo(u32 date, u32 month, u32 year);

/* ---------- DAY FUNCTIONS ---------- */

// Get day of week
void GetRTCDay(s32 *day);

// Display day on LCD
void DisplayRTCDay(u32 day);

// Set day of week
void SetRTCDay(u32 day);

/* ---------- PERIODIC TASK ---------- */

// Flag set every 2 minutes
extern unsigned char rtc_2min_flag;

// Check 2-minute interval
void RTC_Check2Min(void);

#endif
