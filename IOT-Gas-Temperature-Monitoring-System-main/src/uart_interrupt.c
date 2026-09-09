/*------------------- HEADER FILES -------------------*/
#include <LPC21xx.H>     // LPC21xx register definitions
#include "rtc_defines.h"
#include "uart0.h"

/*------------------- GLOBAL VARIABLES -------------------*/
// UART receive buffer and control variables
char buff[350] = "hello";   // Buffer to store received data
char dummy;                 // Dummy variable for clearing interrupt
unsigned char i = 0;        // Buffer index
unsigned char ch;           // Received character
unsigned char r_flag;       // Flag when full message received

/*------------------- UART0 INTERRUPT SERVICE ROUTINE -------------------*/
// Handles UART receive interrupt
void UART0_isr(void) __irq
{
    /* ----- RECEIVE INTERRUPT ----- */
    if((U0IIR & 0x04))              // Check if RX interrupt occurred
    {
        ch = U0RBR;                 // Read received character (clears interrupt)

        if(i<350)                 // Prevent buffer overflow
        {
            buff[i++] = ch;         // Store character in buffer
        }
    }

    /* ----- MESSAGE COMPLETE CHECK ----- */
    if(ch == '\n')                  // End of message detected
    {
        r_flag = 1;                 // Set flag for processing
    }
    else
    {
        dummy = U0IIR;              // Clear other interrupts (TX etc.)
    }

    VICVectAddr = 0;                // End of ISR (acknowledge interrupt)
}

/*------------------- UART INITIALIZATION -------------------*/
// Configure UART0 for communication (9600 baud)
void InitUART0(void)
{
    PINSEL0 |= 0x00000005;   // Enable RXD0 (P0.0) and TXD0 (P0.1)

    U0LCR = 0x83;            // 8-bit data, no parity, 1 stop bit, DLAB=1
    U0DLL = DIVISOR;         // Set baud rate (low byte)
    U0DLM = DIVISOR >> 8;    // Set baud rate (high byte)
    U0LCR = 0x03;            // DLAB=0 (lock divisor)

#if UART_INT_ENABLE > 0

    /* ----- INTERRUPT CONFIGURATION ----- */
    VICIntSelect = 0x00000000;       // Select IRQ (not FIQ)
    VICVectAddr0 = (unsigned)UART0_isr; // ISR address
    VICVectCntl0 = 0x20 | 6;         // Enable slot + UART0 interrupt number
    VICIntEnable = 1 << 6;           // Enable UART0 interrupt

    U0IER = 0x03;                    // Enable RX and THRE interrupts

#endif
}

/*------------------- TRANSMIT FUNCTIONS -------------------*/
// Send one character
void UART0_Tx(char ch)
{
    while (!(U0LSR & 0x20));   // Wait until transmit buffer empty
    U0THR = ch;                // Send character
}

// Receive one character (blocking)
char UART0_Rx(void)
{
    while (!(U0LSR & 0x01));   // Wait until data received
    return U0RBR;
}

// Send string
void UART0_Str(char *s)
{
    while(*s)
        UART0_Tx(*s++);
}

/*------------------- DATA CONVERSION FUNCTIONS -------------------*/
// Send integer as ASCII
void UART0_Int(unsigned int n)
{
    unsigned char a[10] = {0};
    int i = 0;

    if(n == 0)
    {
        UART0_Tx('0');
        return;
    }

    while(n > 0)              // Extract digits (reverse order)
    {
        a[i++] = (n % 10) + 48;
        n = n / 10;
    }

    for(i = i - 1; i >= 0; i--) // Send in correct order
    {
        UART0_Tx(a[i]);
    }
}

// Send float value (2 decimal precision)
void UART0_Float(float f)
{
    int x;
    float temp;

    x = f;                   // Integer part
    UART0_Int(x);

    UART0_Tx('.');

    temp = (f - x) * 100;    // Fractional part (2 digits)
    x = temp;
    UART0_Int(x);
}
