/*
 * interrupt.h
 * Header file for external interrupt (EINT1)
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/* Initialize External Interrupt 1 */
void EINT1_Init(void);

/* EINT1 Interrupt Service Routine */
void EINT1_ISR(void) __irq;

#endif
