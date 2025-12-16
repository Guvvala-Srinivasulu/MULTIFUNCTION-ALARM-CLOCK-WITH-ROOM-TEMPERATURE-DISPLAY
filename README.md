# ⏰ MULTIFUNCTION ALARM CLOCK  
## *with Room Temperature, Day & Date Display*

A compact **embedded real-time clock system** based on the **on-chip RTC of LPC2148**, capable of displaying the **current time, day, date, and room temperature**, along with a **programmable alarm feature**.

The system supports **interrupt-based editing for all time and alarm parameters**, while keeping **temperature sensing read-only** for accuracy and reliability.

---

## ✨ Features

- ⏱ **On-Chip Real-Time Clock (RTC)**  
  Uses the **internal RTC of LPC2148** to display accurate time (HH:MM:SS).

- 📅 **Day & Date Display**  
  Displays **current day (MON–SUN)** and **date (DD/MM/YYYY)**.

- 🌡 **Room Temperature Monitoring (Read-Only)**  
  Continuously senses and displays ambient room temperature.

- ⏰ **Programmable Alarm Function**  
  Alarm time configurable using interrupt-driven editing.

- ⚡ **Interrupt-Based Parameter Editing**  
  External interrupt enables editing of:
  - Time  
  - Day  
  - Date  
  - Alarm Time  
  *(Temperature excluded)*

- 🖥 **16×2 LCD User Interface**  
  Displays time, day, date, temperature, and alarm status.

- 🎛 **Keypad-Based Navigation**  
  Used for increment/decrement and cursor movement.

- ⚠ **Audio Alert Indication**  
  Buzzer activates automatically when alarm time matches RTC.

- 🔁 **Continuous Real-Time Operation**  
  RTC and temperature values update continuously.

---

## 🛠 Hardware Components

- **LPC2148 (ARM7) Microcontroller**  
- **Temperature Sensor (LM35 / DHT11)**  
- **16×2 HD44780-Compatible LCD**  
- **Matrix Keypad**  
- **External Interrupt Switch (EDIT MODE)**  
- **Buzzer (Alarm Output)**  
- **Regulated Power Supply (5V / 3.3V)**  
- **USB-UART Converter (Programming & Debugging)**  

---

## 📌 Pin Configuration

| Signal | Pin | Description |
|------|------|------------|
| LCD Data | P0.8 – P0.15| 8-bit LCD data bus |
| LCD RS | P0.16 | Register select |
| LCD EN | P0.18 | Enable signal |
| Keypad Rows | P1.16 – P1.19 | Row scanning |
| Keypad Columns | P1.20 – P1.23 | Column scanning |
| Buzzer | P0.6 | Alarm output |
| EDIT Interrupt | P0.1 | External Interrupt (EINT0) |

---

## 🧩 Software Overview

- Firmware written in **Embedded C**
- Developed using **Keil µVision IDE**
- Programmed using **Flash Magic**
- Implements:
  - On-chip RTC configuration and reading  
  - External interrupt handling  
  - Keypad scanning logic  
  - LCD command & data routines  
  - Temperature sensor interfacing (read-only)  
  - Alarm time comparison logic  
  - Buzzer control  

---

## 🧑‍💻 User Guide

1. Power ON the system — LCD displays:
   - Current Time  
   - Current Day  
   - Current Date  
   - Room Temperature  
2. Press the **EDIT MODE switch (External Interrupt)**.
3. System enters **editing mode**.
4. Editable parameters:
   - Time (HH:MM:SS)
   - Day (MON–SUN)
   - Date (DD/MM/YYYY)
   - Alarm Time (HH:MM)
5. **Temperature is read-only and cannot be edited**.  
6. Press the interrupt switch again to **save and exit**.
7. System returns to normal run mode.
8. When alarm time matches RTC time, **buzzer activates**.
9. Press any key to stop the alarm.

---

## ⚠ Known Issues

- Alarm triggers once per day unless reset.
- Minor temperature variation due to sensor tolerance.
- Incorrect manual day/date entry may cause mismatch.
- LCD flicker may occur during rapid interrupt transitions.

---

## 📸 Project Images / Screenshots

### Proteus Simulation Overview
![image alt](https://github.com/Guvvala-Srinivasulu/MULTIFUNCTION-ALARM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY/blob/5196f0e5b2af015322def293c3791f280f26cc89/Screenshot%202025-12-16%20162556.png)


### Interrupt-Based Editing Mode Options
![image alt](https://github.com/Guvvala-Srinivasulu/MULTIFUNCTION-ALARM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY/blob/519de7ee4f5224af216579c04d8d941ea0e4b1ba/Screenshot%202025-12-16%20162632.png)


### Time, Day & Date Display Editing Mode Options
![image alt]()  

### Time, Day & Date Display Editing Mode Options
![image alt]()  


---

## 💡 Future Enhancements

- Multiple alarm scheduling
- Snooze functionality using interrupt
- Battery backup for RTC
- Automatic leap-year handling
- OLED / TFT graphical display
- Voice or mobile-based alarm control
- Low-power sleep modes

---

## 📌 Conclusion

The **Multifunction Alarm Clock with Room Temperature, Day & Date Display** efficiently utilizes the **LPC2148 on-chip RTC**, eliminating the need for external RTC or I2C communication.  
Interrupt-driven editing enhances usability while maintaining system accuracy and simplicity.

---

## 🧑‍💻 Developed Using

- Keil µVision IDE  
- ARM7 LPC2148  
- Embedded C  
