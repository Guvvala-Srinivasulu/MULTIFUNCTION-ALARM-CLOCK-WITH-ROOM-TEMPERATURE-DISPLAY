# MULTIFUNCTION-ALARM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY
# ⏰ MULTIFUNCTION ALARM CLOCK  
## *with Room Temperature, Day & Date Display*

A compact **embedded real-time clock system** that displays the **current time, day, date, and room temperature**, while providing a **programmable alarm feature** with intuitive keypad interaction.

This project integrates **timekeeping, calendar tracking, environmental sensing, and alert mechanisms** into a single multifunction embedded solution suitable for home, office, and academic applications.

---

## ✨ Features

- ⏱ **Real-Time Clock (RTC) Display**  
  Displays accurate **current time (HH:MM:SS)** using an RTC module.

- 📅 **Day & Date Display**  
  Shows the **current day (MON–SUN)** and **date (DD/MM/YYYY)** on the LCD.

- 🌡 **Room Temperature Monitoring**  
  Continuously measures and displays ambient room temperature.

- ⏰ **Programmable Alarm Function**  
  User-configurable alarm time with buzzer alert.

- 🖥 **16×2 LCD User Interface**  
  Displays **time, day, date, temperature, and alarm status**.

- 🎛 **Keypad-Based Configuration**  
  Easy keypad-based setting of time, day, date, and alarm.

- ⚠ **Audio Alert Indication**  
  Buzzer activates automatically when alarm time is reached.

- 🔁 **Continuous Real-Time Operation**  
  Updates time, date, day, and temperature continuously.

---

## 🛠 Hardware Components

- **LPC2148 (ARM7) Microcontroller**  
- **RTC Module (DS1307 / On-Chip RTC)**  
- **Temperature Sensor (LM35 / DHT11)**  
- **16×2 HD44780-Compatible LCD**  
- **Matrix Keypad**  
- **Buzzer (Alarm Output)**  
- **Push Buttons (Mode / Stop Alarm)**  
- **Regulated Power Supply (5V / 3.3V)**  
- **USB-UART Converter (Programming & Debugging)**  

---

## 📌 Pin Configuration

| Signal | Pin | Description |
|------|------|------------|
| LCD Data | P0.0 – P0.7 | 8-bit LCD data bus |
| LCD RS | P0.9 | Register select |
| LCD EN | P0.8 | Enable signal |
| Keypad Rows | P1.20 – P1.23 | Row scanning lines |
| Keypad Columns | P1.24 – P1.27 | Column scanning lines |
| Buzzer | P0.6 | Alarm output |
| RTC SDA | P0.27 | I2C data line |
| RTC SCL | P0.28 | I2C clock line |

---

## 🧩 Software Overview

- Firmware written in **Embedded C**
- Developed using **Keil µVision IDE**
- Programmed using **Flash Magic**
- Implements:
  - RTC time, day & date read/write routines  
  - Keypad scanning logic  
  - LCD command & data handling  
  - Temperature sensor interface  
  - Alarm comparison logic  
  - Buzzer control  

---

## 🧭 System Architecture

![System Architecture](images/alarmclock_architecture.png)  
*Figure 1: System architecture showing RTC, temperature sensor, LCD, keypad, and buzzer.*

---

## 🧑‍💻 User Guide

1. Power ON the system — LCD displays:
   - Current Time  
   - Current Day  
   - Current Date  
   - Room Temperature  
2. Press the **mode key** to enter configuration mode.
3. Configure:
   - Time (HH:MM:SS)
   - Day (MON–SUN)
   - Date (DD/MM/YYYY)
   - Alarm Time (HH:MM)
4. Keypad controls:
   - `→` Move to next field  
   - `←` Move to previous field  
   - `↑` Increment value  
   - `↓` Decrement value  
5. Save the settings and exit.
6. System returns to normal display mode.
7. When RTC time matches alarm time, **buzzer is activated**.
8. Press any key to stop the alarm.

---

## ⚠ Known Issues

- Alarm triggers once per day unless reset.
- Minor temperature variation due to sensor tolerance.
- LCD flicker may occur during rapid updates.
- Incorrect day/date entry may cause mismatch unless RTC is properly set.

---

## 📸 Project Images / Screenshots

### Proteus Simulation Overview
![Proteus Overview](images/proteus_alarmclock_overview.png)  
*Figure 2: Complete alarm clock system simulated in Proteus.*

### Time, Day & Date Display
![LCD Output](images/proteus_alarmclock_lcd.png)  
*Figure 3: LCD displaying time, day, date, and room temperature.*

### Alarm Trigger Condition
![Alarm Trigger](images/proteus_alarmclock_alarm.png)  
*Figure 4: Buzzer activation when alarm time is reached.*

---

## 💡 Future Enhancements

- Multiple alarms (daily, weekly scheduling)
- Snooze functionality
- Battery backup for RTC
- Automatic day/date correction
- OLED / TFT graphical display
- Wireless time synchronization (NTP)
- Mobile app integration for alarm control

---

## 📌 Conclusion

The **Multifunction Alarm Clock with Room Temperature, Day & Date Display** successfully combines **real-time clock functionality, calendar tracking, temperature monitoring, and alarm automation** in a single embedded system.  
Its reliability and extensibility make it ideal for both practical use and academic projects.

---

## 🧑‍💻 Developed Using

- Keil µVision IDE  
- ARM7 LPC2148  
- Embedded C  
- RTC & Temperature Sensors  

---

> ⚠️ Note  
> Add real Proteus screenshots inside the `images/` folder before uploading to GitHub.
