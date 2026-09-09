/*------------------- HEADER FILES -------------------*/
#include <LPC21xx.h>   // LPC21xx register definitions
#include "delay.h"
#include "types.h"
#include "defines.h"
#include "lcd.h"

/*------------------- PIN CONFIGURATION -------------------*/
// LCD data lines connected from P0.16 to P0.23
#define LCD_data 16

// Control pins
#define RS 8    // Register Select
#define RW 10   // Read/Write
#define EN 9    // Enable

/*------------------- LCD INITIALIZATION -------------------*/
// Initialize LCD in 8-bit mode
void InitLCD(void)
{
    // Configure data + control pins as output
    IODIR0 |= (0xff<<LCD_data) | (1<<RS) | (1<<RW) | (1<<EN);

    // LCD initialization sequence
    delay_ms(15);
    CmdLCD(0x30);
    delay_ms(5);
    CmdLCD(0x30);
    delay_us(100);
    CmdLCD(0x30);

    CmdLCD(0x38);   // 8-bit mode, 2-line display
    CmdLCD(0x0C);   // Display ON, cursor OFF
    CmdLCD(0x01);   // Clear display
    CmdLCD(0x06);   // Entry mode (cursor increment)
}

/*------------------- LOW LEVEL WRITE -------------------*/
// Send data/command byte to LCD
void DispLCD(u8 val)
{
    IOCLR0 = 1<<RW;                     // Write mode

    WRITEBYTE(IOPIN0,16,val);           // Send 8-bit data to P0.16–P0.23

    IOSET0 = 1<<EN;                     // Enable pulse HIGH
    delay_us(1);
    IOCLR0 = 1<<EN;                     // Enable pulse LOW

    delay_ms(2);                        // Command execution delay
}

/*------------------- DATA / COMMAND FUNCTIONS -------------------*/
// Send character to LCD
void CharLCD(s8 dat)
{
    IOSET0 = 1<<RS;     // RS = 1 ? Data mode
    DispLCD(dat);
}

// Send command to LCD
void CmdLCD(u8 cmd)
{
    IOCLR0 = 1<<RS;     // RS = 0 ? Command mode
    DispLCD(cmd);
}

/*------------------- DISPLAY FUNCTIONS -------------------*/
// Display string
void StrLCD(char *ptr)
{
    while(*ptr != '\0')
    {
        CharLCD(*ptr++);
    }
}

// Display integer
void IntLCD(s32 num)
{
    s8 a[10];
    s32 i = 0;

    if(num == 0)
    {
        CharLCD('0');
    }
    else
    {
        if(num < 0)
        {
            CharLCD('-');
            num = -num;
        }

        while(num)              // Extract digits
        {
            a[i++] = num % 10 + 48;
            num /= 10;
        }

        for(i = i - 1; i >= 0; i--) // Display in correct order
        {
            CharLCD(a[i]);
        }
    }
}

// Display floating point number
void F32LCD(f32 FN, u32 nDP)
{
    u32 n;
    s32 i;

    if(FN < 0.0)
    {
        CharLCD('-');
        FN = -FN;
    }

    n = FN;
    IntLCD(n);           // Integer part
    CharLCD('.');

    for(i = 0; i < nDP; i++)
    {
        FN = (FN - n) * 10;
        n = FN;
        CharLCD(n + 48); // Fraction digits
    }
}

/*------------------- CUSTOM CHARACTER -------------------*/
// Write custom pattern into CGRAM
void WriteTOCGRAM(void)
{
    s8 i;
    s8 a[] = {0x00,0x1F,0x11,0x11,0x1F,0x00};

    CmdLCD(0x60);        // CGRAM address

    for(i = 0; i < 8; i++)
    {
        CharLCD(a[i]);
    }
}
