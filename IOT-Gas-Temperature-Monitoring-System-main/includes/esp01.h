/*
 * esp01.h
 * Header file for ESP8266 (ESP-01) WiFi communication
 * Used for IoT communication with ThingSpeak
 */

#ifndef _ESP01_H_
#define _ESP01_H_

#include "types.h"

/* ---------- WiFi & SERVER SETUP ---------- */

// Connect ESP8266 to WiFi Access Point
void esp01_connectAP(void);

/* ---------- THINGSPEAK DATA UPLOAD ---------- */

// Send temperature data to ThingSpeak
void esp01_sendToThingspeak(int value);

// Send gas alert status
void esp01_sendGas(char value);

// Send temperature alert status
void esp01_sendAlert(char value);

// Send setpoint value to cloud
void esp01_sendSetpoint(int value);

/* ---------- THINGSPEAK DATA READ ---------- */

// Read setpoint value from ThingSpeak
int esp01_readSetpoint(void);

// Extract setpoint from received JSON buffer
void extract_sp(u8 *buffer);

#endif
