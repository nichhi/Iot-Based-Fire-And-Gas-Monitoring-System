/*------------------- HEADER FILES -------------------*/
// LPC21xx microcontroller register definitions
#include <LPC21xx.h>

// Peripheral modules
#include "lcd.h"
#include "adc.h"
#include "lm35.h"
#include "delay.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "esp01.h"
#include "rtc.h"
#include "interrupt.h"
#include "keypad.h"
#include "uart0.h"

/*------------------- MACROS -------------------*/
// Hardware pin definitions
#define BUZZER 12
#define GAS_PIN 10

// EEPROM address for storing temperature setpoint
#define SETPOINT_ADDR 0x0000

/*------------------- GLOBAL VARIABLES -------------------*/
// Sensor and system variables
f32 temp;                 // Temperature value
int setpoint, num;        // Local setpoint and keypad input
int cloud_setpoint;       // Setpoint received from cloud

// Status flags
int gas_flag = 0;         // Gas detection flag
int temp_flag = 0;        // Temperature alert flag

// RTC time variables
s32 hr, min, sec;

// External flags (from interrupt/RTC modules)
extern unsigned char rtc_2min_flag;
extern volatile int setpoint_request;

/*------------------- MAIN FUNCTION -------------------*/
int main()
{
    /* ---------- GPIO CONFIGURATION ---------- */
    IODIR0 |= (1<<BUZZER);     // Set buzzer pin as output
    IODIR0 &= ~(1<<GAS_PIN);   // Set gas sensor pin as input

    /* ---------- INITIALIZATION ---------- */
    InitLCD();
    Init_ADC();
    Init_SPI0();
    InitUART0();
    RTC_Init();
    EINT1_Init();
    KeyadInit();

    /* ---------- STARTUP DISPLAY ---------- */
    CmdLCD(0x01);
    StrLCD("Gas Temp Monitor");
    CmdLCD(0xC0);
    StrLCD("IoT System");
    delay_ms(2000);

    /* ---------- WIFI CONNECTION ---------- */
    esp01_connectAP();
    delay_ms(5000);

    /* ---------- SETPOINT INITIALIZATION ---------- */
    ByteWrite(SETPOINT_ADDR,35);        // Default setpoint
    setpoint = ByteRead(SETPOINT_ADDR); // Load setpoint

    /* ---------- MAIN LOOP ---------- */
    while(1)
    {
        /* ----- HANDLE USER INPUT (INTERRUPT) ----- */
        if(setpoint_request == 1)
        {
            setpoint_request = 0;

            CmdLCD(0x01);
            StrLCD("Setpoint:");
            CmdLCD(0xC0);

            num = Readnum();                         // Read keypad input
            ByteWrite(SETPOINT_ADDR, num);           // Save to EEPROM
            setpoint = ByteRead(SETPOINT_ADDR);      // Update value

            CmdLCD(0x01);
            StrLCD("Updated");
            delay_ms(2000);

            esp01_sendSetpoint(setpoint);            // Sync with cloud
        }

        /* ----- DISPLAY TIME & TEMPERATURE ----- */
        GetRTCTimeInfo(&hr,&min,&sec);

        CmdLCD(0x80);
        CharLCD((hr/10)+'0'); CharLCD((hr%10)+'0');
        CharLCD(':');
        CharLCD((min/10)+'0'); CharLCD((min%10)+'0');
        CharLCD(':');
        CharLCD((sec/10)+'0'); CharLCD((sec%10)+'0');

        Read_LM35(&temp,'C');

        CmdLCD(0xC0);
        StrLCD("T:");
        IntLCD((int)temp);
        StrLCD(" SP:");
        IntLCD(setpoint);

        /* ----- GAS DETECTION ----- */
        if(((IOPIN0>>GAS_PIN)&1)==0)
        {
            if(gas_flag==0)
            {
                IOSET0 = 1<<BUZZER;
                esp01_sendGas('1');
                gas_flag = 1;
            }
        }
        else
        {
            gas_flag = 0;
        }

        /* ----- TEMPERATURE ALERT ----- */
        if((int)temp > setpoint)
        {
            if(temp_flag==0)
            {
                IOSET0 = 1<<BUZZER;
                esp01_sendAlert('1');
                temp_flag = 1;
            }
        }
        else
        {
            temp_flag = 0;
        }

        /* ----- BUZZER CONTROL ----- */
        if(gas_flag==0 && temp_flag==0)
        {
            IOCLR0 = 1<<BUZZER;
        }

        /* ----- CLOUD SYNC (EVERY 2 MINUTES) ----- */
        RTC_Check2Min();

        if(rtc_2min_flag)
        {
            rtc_2min_flag = 0;

            esp01_sendToThingspeak((int)temp);
            cloud_setpoint = esp01_readSetpoint();

            CmdLCD(0x01);
            StrLCD("Cloud:");
            IntLCD(cloud_setpoint);
            delay_ms(2000);

            if(cloud_setpoint>0 && cloud_setpoint!=setpoint)
            {
                ByteWrite(SETPOINT_ADDR, cloud_setpoint);
                setpoint = ByteRead(SETPOINT_ADDR);
            }
        }

        delay_ms(150);
    }
}
