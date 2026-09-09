/*------------------- HEADER FILES -------------------*/
#include <string.h>     // String handling functions
#include "uart0.h"      // UART communication (ESP01 interface)
#include "delay.h"
#include "lcd.h"
#include <stdlib.h>     // atoi() conversion
#include "esp01.h"
#include "types.h"

/*------------------- GLOBAL VARIABLES -------------------*/
// Shared UART buffer and control variables
extern char buff[350];
extern unsigned char i;
extern unsigned char r_flag;

int rsp;   // Stores parsed response (setpoint from cloud)

/*------------------- WIFI CONNECTION -------------------*/
// Connect ESP01 to WiFi Access Point using AT commands
void esp01_connectAP()
{
    /* ----- BASIC AT CHECK ----- */
    CmdLCD(0x01);
    StrLCD("AT");
    UART0_Str("AT\r\n");           // Check ESP response

    i=0; memset(buff,'\0',350);
    while(i<4);                   // Wait for response
    delay_ms(500);

    if(!strstr(buff,"OK"))        // Validate response
    {
        StrLCD("ERROR");
        return;
    }

    /* ----- DISABLE ECHO ----- */
    UART0_Str("ATE0\r\n");        // Disable command echo
    i=0; memset(buff,'\0',350);
    while(i<4);
    delay_ms(500);

    if(!strstr(buff,"OK"))
        return;

    /* ----- SINGLE CONNECTION MODE ----- */
    UART0_Str("AT+CIPMUX=0\r\n"); // Single connection
    i=0; memset(buff,'\0',350);
    while(i<4);
    delay_ms(500);

    if(!strstr(buff,"OK"))
        return;

    /* ----- DISCONNECT PREVIOUS WIFI ----- */
    UART0_Str("AT+CWQAP\r\n");
    i=0; memset(buff,'\0',350);
    while(i<4);
    delay_ms(1500);

    /* ----- CONNECT TO WIFI ----- */
    UART0_Str("AT+CWJAP=\"A\",\"12345678\"\r\n"); // SSID & Password
    i=0; memset(buff,'\0',350);
    while(i<4);
    delay_ms(2500);

    if(strstr(buff,"WIFI CONNECTED"))
    {
        CmdLCD(0x01);
        StrLCD("WiFi OK");
    }
}

/*------------------- SEND TEMPERATURE (FIELD1) -------------------*/
// Sends temperature data to ThingSpeak cloud
void esp01_sendToThingspeak(int val)
{
	CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("Temp SEND");
	delay_ms(500);
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i=0; memset(buff,'\0',350);
    while(i<5);
    delay_ms(2500);

    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
    {
        UART0_Str("AT+CIPSEND=50\r\n");
        delay_ms(500);

        UART0_Str("GET /update?api_key=WZPLGD53K501HBDA&field1=");
        UART0_Int(val);           // Send temperature
        UART0_Str("\r\n\r\n");

        delay_ms(5000);

        if(strstr(buff,"OK"))
        {
            CmdLCD(0x01);
            StrLCD("TEMP UPDATED");
        }
    }
}

/*------------------- SEND GAS STATUS (FIELD2) -------------------*/
// Sends gas detection status
void esp01_sendGas(char val)
{
	CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("SEND Gas");
	delay_ms(500);
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i=0; memset(buff,'\0',350);
    while(i<5);
    delay_ms(3000);

    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
    {
        UART0_Str("AT+CIPSEND=49\r\n");
        delay_ms(1000);

        UART0_Str("GET /update?api_key=WZPLGD53K501HBDA&field2=");
        UART0_Tx(val);            // Send gas flag
        UART0_Str("\r\n\r\n");

        delay_ms(5000);

        if(strstr(buff,"OK"))
        {
            CmdLCD(0x01);
            StrLCD("GAS UPDATED");
        }
    }
}

/*------------------- SEND TEMP ALERT (FIELD3) -------------------*/
// Sends alert when temperature exceeds setpoint
void esp01_sendAlert(char val)
{
	CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("Temp Alert");
	delay_ms(500);
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i=0; memset(buff,'\0',350);
    while(i<5);
    delay_ms(3000);

    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
    {
        UART0_Str("AT+CIPSEND=49\r\n");
        delay_ms(1000);

        UART0_Str("GET /update?api_key=WZPLGD53K501HBDA&field3=");
        UART0_Tx(val);
        UART0_Str("\r\n\r\n");

        delay_ms(5000);

        if(strstr(buff,"OK"))
        {
            CmdLCD(0x01);
            StrLCD("ALERT UPDATED");
        }
    }
}

/*------------------- SEND SETPOINT -------------------*/
// Sends updated setpoint to cloud
void esp01_sendSetpoint(int val)
{
	CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("SETPOINT SEND");
	delay_ms(500);
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i=0; memset(buff,'\0',350);
    while(i<5);
    delay_ms(3000);

    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
    {
        UART0_Str("AT+CIPSEND=50\r\n");
        delay_ms(1000);

        UART0_Str("GET /update?api_key=TUSF1RM72UGUU100&field1=");
        UART0_Int(val);
        UART0_Str("\r\n\r\n");

        delay_ms(5000);

        if(strstr(buff,"OK"))
        {
            CmdLCD(0x01);
            StrLCD("SP UPDATED");
        }
    }
}

/*------------------- READ SETPOINT FROM CLOUD -------------------*/
// Reads latest setpoint from ThingSpeak channel
int esp01_readSetpoint()
{
    u8 arr[350];
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("READ SP");
	delay_ms(1000);
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    i=0; memset(buff,'\0',350);
    while(i<5);
    delay_ms(2500);

    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
    {
        UART0_Str("AT+CIPSEND=72\r\n");
        delay_ms(500);

        UART0_Str("GET /channels/3282092/fields/1.json?api_key=VPB8LF3710OFI7HY&results=1\r\n");

        delay_ms(10000);

        strcpy((char *)arr,buff);

        if(strstr(buff,"field1"))
        {
            extract_sp(arr);   // Extract value from JSON
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    return rsp;   // Return extracted setpoint
}

/*------------------- EXTRACT SETPOINT -------------------*/
// Extract numeric setpoint from JSON response
void extract_sp(u8 *p)
{
    u8 r[5], l=0;
    char *q = strstr((char *)p,"field1");

    if(q)
    {
        q = strchr(q,':');     // Move to value
        q = q + 2;

        while(*q != '"')       // Extract digits
        {
            r[l++] = *q++;
        }
        r[l] = '\0';
    }

    rsp = atoi((char *)r);     // Convert string to integer

    CmdLCD(0x01);
    StrLCD("Remote SP:");
    IntLCD(rsp);
}
