/*------------------- HEADER FILES -------------------*/
#include "adc.h"     // ADC read functions
#include "types.h"

/*------------------- LM35 READ FUNCTION -------------------*/
// Reads temperature from LM35 sensor
// choice: 'C' ? Celsius, 'F' ? Fahrenheit
void Read_LM35(f32 *degT, u8 choice)
{
    static u32 flag;     // Ensures ADC initialized only once
    u32 dVal;            // Digital ADC value
    f32 eAR;             // Analog voltage (0–3.3V)
    f32 degC, degF;      // Temperature values

    /* ----- ONE-TIME ADC INITIALIZATION ----- */
    if(flag == 0)
    {	
        Init_ADC();      // Initialize ADC
        flag = 1;	
    }	

    /* ----- READ SENSOR VALUE ----- */
    Read_ADC(1, &dVal, &eAR);   // Read from channel 1 (P0.28)

    /* ----- CONVERT TO TEMPERATURE ----- */
    degC = eAR * 100;           // LM35: 10mV/°C ? 0.01V = 1°C

    degF = (degC * 9.0 / 5.0) + 32;  // Convert to Fahrenheit

    /* ----- RETURN RESULT BASED ON CHOICE ----- */
    if(choice == 'C')
        *degT = degC;
    else if(choice == 'F')
        *degT = degF;
}
