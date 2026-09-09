# 🔥 IoT Based Gas & Temperature Monitoring System

## 📌 Project Overview

This project is an **embedded IoT system** designed to monitor **temperature and gas levels** in real time. It alerts users locally using a buzzer and remotely using cloud updates via Wi-Fi.

The system also allows users to **set and update a temperature threshold (setpoint)** using a keypad or remotely through the cloud.

---

## 🎯 Objectives

* Monitor environmental **temperature (LM35 sensor)**
* Detect **gas leakage**
* Provide **real-time alerts**
* Store setpoint in **EEPROM (non-volatile memory)**
* Send data to **ThingSpeak cloud**
* Enable **remote setpoint update**

---

## 🧰 Components Used

* LPC2148 Microcontroller
* LM35 Temperature Sensor
* Gas Sensor (Digital Output)
* 16x2 LCD Display
* 4x4 Matrix Keypad
* ESP8266 (ESP-01 Wi-Fi Module)
* External EEPROM (SPI)
* Buzzer
* RTC (Real-Time Clock)

---

## ⚙️ Features

* 🌡️ Real-time temperature monitoring
* 🧪 Gas detection with alert
* 🔔 Buzzer alert system
* ☁️ Cloud integration (ThingSpeak)
* ⌨️ User input via keypad
* 💾 EEPROM storage for setpoint
* ⏱️ Periodic cloud updates using RTC
* ⚡ Interrupt-based user input

---

## 🧠 Working Principle

1. **Temperature Reading**

   * LM35 sensor outputs analog voltage
   * ADC converts it into digital value
   * Converted to temperature (°C)

2. **Gas Detection**

   * Gas sensor provides digital signal
   * If gas detected → alert triggered

3. **Setpoint Handling**

   * User enters setpoint using keypad
   * Stored in EEPROM
   * Can also be updated from cloud

4. **Alert System**

   * If temperature > setpoint OR gas detected:

     * Buzzer ON
     * Cloud alert sent

5. **Cloud Communication**

   * ESP8266 sends data to ThingSpeak
   * Receives updated setpoint

6. **RTC Scheduling**

   * Every 2 minutes:

     * Data sent to cloud
     * Setpoint synced

---

## 📁 Project Structure

```
├── main.c                → Main application logic
├── esp01.c              → Wi-Fi (ESP8266) communication
├── uart_interrupt.c     → UART with interrupt handling
├── lcd.c                → LCD display functions
├── rtc.c                → Real-Time Clock handling
├── adc.c                → ADC configuration & reading
├── lm35.c               → Temperature calculation
├── keypad.c             → Keypad input handling
├── external_interrupt.c → Interrupt for setpoint update
├── spi.c                → SPI communication
├── spi_eeprom.c         → EEPROM read/write
├── delay.c              → Software delays
```

---

## 🔄 System Flow

```
Sensors → ADC → Microcontroller → LCD Display
                         ↓
                    Compare with Setpoint
                         ↓
                Alert (Buzzer + Cloud)
                         ↓
               EEPROM + ThingSpeak Sync
```

---

## 📡 ThingSpeak Fields Used

Channel 1:
* **Field 1** → Temperature
* **Field 2** → Gas status
* **Field 3** → Temperature alert
Channel 2:
* **Field 1** → Setpoint 

---

## ⚠️ Limitations

* Requires stable WiFi connection for cloud updates
* Blocking functions used in keypad and delays
* No debounce hardware for keypad
* LM35 provides moderate accuracy (not industrial-grade)
* No battery backup (power failure affects operation) 
* Limited to basic alert system (no mobile app integration)

---

📡 Applications
*Industrial gas leakage monitoring systems
*Smart home safety systems
*Laboratories and chemical industries
*Temperature monitoring in storage environments
*IoT-based environmental monitoring

## 🚀 Future Improvements

* Use hardware timers instead of software delay
* Add mobile app for monitoring
* Improve error handling
* Add multiple sensor support
* Use RTOS for better performance

---

## 👩‍💻 Author

**Lingamdinne Anila**

---

## 📜 License

This project is for educational purposes.
