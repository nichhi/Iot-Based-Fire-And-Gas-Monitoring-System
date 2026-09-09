/*------------------- HEADER FILES -------------------*/
#include "types.h"
#include <LPC21xx.h>      // ADC register definitions
#include "delay.h"
#include "adc_defines.h"

/*------------------- ADC INITIALIZATION -------------------*/
// Configure ADC pins and enable ADC module
void Init_ADC(void)
{
    // Configure P0.28 as AIN1 (Analog input channel 1)
    PINSEL1 &= ~((u32)0xFF << 22);   // Clear bits for P0.27–P0.30
    PINSEL1 |= AIN1_0_28;            // Select AIN1 function

    // Configure ADC Control Register
    ADCR |= (CLKDIV << CLKDIV_BITS_START) | // Set ADC clock
            (1 << PDN_BIT);                 // Power ON ADC
}

/*------------------- ADC READ FUNCTION -------------------*/
// Read analog value from selected channel
void Read_ADC(u32 chNo, u32 *dVal, f32 *eAR)
{
    /* ----- CHANNEL SELECTION ----- */
    ADCR &= 0xFFFFFF00;              // Clear previous channel selection
    ADCR |= (1 << chNo);             // Select required ADC channel

    /* ----- START CONVERSION ----- */
    ADCR |= (1 << CONV_START_BIT);   // Start ADC conversion

    delay_us(3);                     // Minimum conversion delay

    /* ----- WAIT FOR COMPLETION ----- */
    while(((ADDR >> DONE_BIT) & 1) == 0); // Wait until DONE = 1

    /* ----- STOP CONVERSION ----- */
    ADCR &= ~(1 << CONV_START_BIT);

    /* ----- READ RESULT ----- */
    *dVal = (ADDR >> RESULT_BITS_START) & 1023; // 10-bit result (0–1023)

    /* ----- CONVERT TO VOLTAGE ----- */
    *eAR = (*dVal * (3.3 / 1023));   // Convert to analog voltage (0–3.3V)
}
