#include<LPC21xx.h>
#include <stdlib.h>
#include "lcd.h"
#include "delay.h"
#include "types.h"
#include"KeyPad_Defines.h"

/* ---------- KEYPAD INITIALIZATION ---------- */
void KeyadInit(void)
{
	// Configure row pins (R0–R3) as OUTPUT
	IODIR1|=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3)); // P1.16–P1.19

	// Configure column pins (C0–C3) as INPUT
	IODIR1&=~((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));
}

/* ---------- COLUMN STATUS CHECK ---------- */
int ColStat(void)
{
	// If all column lines HIGH ? no key pressed
	if(((IOPIN1>>C0)&0xf)==0xf)
		return 1;
	else
		return 0;
}

/* ---------- READ SINGLE KEY ---------- */
char ReadKeyVal(void)
{
	char RowVal,ColVal;

	// Wait until a key is pressed
	while(ColStat());

	/* ----- ROW SCANNING ----- */

	// Check Row 0
	IOCLR1=1<<R0;
	IOSET1=((1<<R1)|(1<<R2)|(1<<R3));
	if(((IOPIN1>>C0)&0xf)!=0xf)
	{
		RowVal=0;
		goto ColCheck;
	}

	// Check Row 1
	IOCLR1=1<<R1;
	IOSET1=((1<<R0)|(1<<R2)|(1<<R3));
	if(((IOPIN1>>C0)&0xf)!=0xf)
	{
		RowVal=1;
		goto ColCheck;
	}

	// Check Row 2
	IOCLR1=1<<R2;
	IOSET1=((1<<R0)|(1<<R1)|(1<<R3));
	if(((IOPIN1>>C0)&0xf)!=0xf)
	{
		RowVal=2;
		goto ColCheck;
	}

	// Check Row 3
	IOCLR1=1<<R3;
	IOSET1=((1<<R0)|(1<<R1)|(1<<R2));
	if(((IOPIN1>>C0)&0xf)!=0xf)
		RowVal=3;

ColCheck:

	/* ----- COLUMN DETECTION ----- */
	if(((IOPIN1>>C0)&1)==0)
		ColVal=0;
	else if(((IOPIN1>>C1)&1)==0)
		ColVal=1;
	else if(((IOPIN1>>C2)&1)==0)
		ColVal=2;
	else
		ColVal=3;

	/* ----- WAIT FOR KEY RELEASE (DEBOUNCE) ----- */
	while(((IOPIN1>>C0)&0xf)!=0xf);
	delay_ms(50);

	// Reset all rows
	IOCLR1=15<<R0;

	// Return key value from lookup table
	return(LUT[RowVal][ColVal]);
}

/* ---------- MULTI-DIGIT NUMBER INPUT ---------- */
u32 Readnum(void)
{
	u8 a[10],key;
	s32 i=0;

	// Move cursor to second line
	CmdLCD(0xC0);

	while(1)
	{
		key = ReadKeyVal();

		// Wait until key released
		while(ColStat()==0);
		delay_ms(200);

		/* ----- DIGIT INPUT ----- */
		if((key>='0') && (key<='9'))
		{
			a[i]=key;             // Store digit
			CharLCD(a[i++]);      // Display digit
		}

		/* ----- CONFIRM INPUT (D KEY) ----- */
		else if(key=='D')
		{
			a[i]='\0';            // End string
			break;
		}

		/* ----- DELETE LAST DIGIT (C KEY) ----- */
		else if(key=='C')
		{
			if(i>0)
			{
				i--;
				CmdLCD(0xC0+i);   // Move cursor back
				CharLCD(' ');     // Erase character
				CmdLCD(0xC0+i);   // Reset cursor
			}
		}
	}

	// Convert string to integer
	return atoi((char *)a);
}
