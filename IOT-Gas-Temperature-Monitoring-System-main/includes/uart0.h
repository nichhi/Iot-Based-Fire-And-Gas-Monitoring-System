/*
 * uart0.h
 * Header file for UART0 communication (LPC21xx)
 */

#ifndef _UART0_H_
#define _UART0_H_

/* ---------- UART CONFIGURATION ---------- */

// Enable UART interrupt (1 = enabled, 0 = disabled)
#define UART_INT_ENABLE 1

/* ---------- CLOCK & BAUD RATE ---------- */

#define FOSC 12000000      // 12 MHz crystal

// Baud rate
#define BAUD 9600

// UART divisor for baud rate generation
#define DIVISOR (PCLK / (16 * BAUD))

/* ---------- FUNCTION PROTOTYPES ---------- */

// Initialize UART0
void InitUART0(void);

// Send single character
void UART0_Tx(char ch);

// Receive single character
char UART0_Rx(void);

// Send string
void UART0_Str(char *str);

// Send integer
void UART0_Int(unsigned int value);

// Send float
void UART0_Float(float value);

#endif
