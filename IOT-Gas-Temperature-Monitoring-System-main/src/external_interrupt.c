/*------------------- HEADER FILES -------------------*/
#include <LPC21xx.h>     // Interrupt register definitions
#include "keyPad.h"
#include "spi_eeprom.h"
#include "lcd.h"
#include "esp01.h"
#include "delay.h"

/*------------------- GLOBAL VARIABLES -------------------*/
// Setpoint shared with main program
extern unsigned int setpoint;

// Flag to notify main loop about interrupt event
volatile int setpoint_request = 0;

/*------------------- EINT1 INTERRUPT SERVICE ROUTINE -------------------*/
// Triggered when external interrupt occurs (e.g., button press)
void EINT1_ISR(void) __irq
{
    /* ----- SET FLAG FOR MAIN LOOP ----- */
    setpoint_request = 1;   // Request setpoint update

    /* ----- CLEAR INTERRUPT FLAG ----- */
    EXTINT = (1 << 1);      // Clear EINT1 interrupt flag

    /* ----- TEMPORARILY DISABLE INTERRUPT ----- */
    VICIntEnClr = (1 << 15);

    /*
    NOTE:
    Heavy operations like:
    - LCD display
    - Keypad input
    - EEPROM write
    - ESP communication

    are avoided inside ISR and handled in main loop.
    (Good design practice)
    */

    /* ----- RE-ENABLE INTERRUPT ----- */
    VICIntEnable = (1 << 15);

    VICVectAddr = 0;        // End of ISR (acknowledge interrupt)
}

/*------------------- INTERRUPT INITIALIZATION -------------------*/
// Configure EINT1 (External Interrupt 1)
void EINT1_Init(void)
{
    /* ----- PIN CONFIGURATION ----- */
    PINSEL0 |= (2 << 28);   // Configure P0.15 as EINT1

    /* ----- INTERRUPT MODE ----- */
    EXTMODE |= (1 << 1);    // Edge-triggered interrupt
    EXTPOLAR &= ~(1 << 1);  // Falling edge trigger

    /* ----- VIC CONFIGURATION ----- */
    VICIntSelect &= ~(1 << 15);             // Select IRQ (not FIQ)

    VICVectAddr1 = (unsigned long)EINT1_ISR; // ISR address
    VICVectCntl1 = (1 << 5) | 15;            // Enable slot + interrupt number

    VICIntEnable = (1 << 15);               // Enable EINT1 interrupt
}
