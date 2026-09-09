/*------------------- HEADER FILES -------------------*/
#include <LPC21xx.h>     // LPC21xx RTC register definitions
#include "rtc.h"
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"

/*------------------- GLOBAL DATA -------------------*/
// Days of the week (for display)
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// Flag to trigger task every 2 minutes
unsigned char rtc_2min_flag = 0;

// Stores previous time in seconds (for comparison)
unsigned int previous_total_sec = 0;

/*------------------- RTC INITIALIZATION -------------------*/
// Initialize RTC with prescaler values
void RTC_Init(void) 
{
    CCR = 1<<1;           // Reset RTC
    PREINT = PREINT_VAL;  // Integer prescaler
    PREFRAC = PREFRAC_VAL;// Fractional prescaler
    CCR = 1<<0;           // Enable RTC
}

/*------------------- TIME FUNCTIONS -------------------*/
// Get current time
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
    *hour = HOUR;
    *minute = MIN;
    *second = SEC;
}

// Display time on LCD (HH:MM:SS)
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
    CmdLCD(GOTO_LINE1_POS0);

    CharLCD((hour/10)+48);
    CharLCD((hour%10)+48);
    CharLCD(':');

    CharLCD((minute/10)+48);
    CharLCD((minute%10)+48);
    CharLCD(':');

    CharLCD((second/10)+48);
    CharLCD((second%10)+48);
}

// Set RTC time
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
    HOUR = hour;
    MIN = minute;
    SEC = second;
}

/*------------------- DATE FUNCTIONS -------------------*/
// Get current date
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
    *date = DOM;
    *month = MONTH;
    *year = YEAR;
}

// Display date (DD/MM/YYYY)
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((date/10)+48);
    CharLCD((date%10)+48);
    CharLCD('/');

    CharLCD((month/10)+48);
    CharLCD((month%10)+48);
    CharLCD('/');

    IntLCD(year);
}

// Set RTC date
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    DOM = date;
    MONTH = month;
    YEAR = year;	
}

/*------------------- DAY FUNCTIONS -------------------*/
// Get day of week (0–6)
void GetRTCDay(s32 *day)
{
    *day = DOW;
}

// Display day (SUN–SAT)
void DisplayRTCDay(u32 dow)
{
    CmdLCD(0x8A);
    StrLCD(week[dow]);
}

// Set day of week
void SetRTCDay(u32 day)
{
    DOW = day;
}

/*------------------- PERIODIC TASK (2 MINUTES) -------------------*/
// Check if 2 minutes elapsed
void RTC_Check2Min(void)
{
    unsigned int current_total_sec;

    // Convert current time to total seconds
    current_total_sec = (HOUR * 3600) + (MIN * 60) + SEC;

    // Compare with previous time
    if((current_total_sec - previous_total_sec) >= 120)
    {
        rtc_2min_flag = 1;            // Set flag
        previous_total_sec = current_total_sec;
    }
}
