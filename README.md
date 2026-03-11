# 🌱 IRIBOTS Smart Irrigation System

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?logo=arduino&logoColor=white)
![ESP8266](https://img.shields.io/badge/ESP8266-WiFi-blue)
![IoT](https://img.shields.io/badge/IoT-Smart%20Agriculture-green)
![Blynk](https://img.shields.io/badge/Blynk-IoT-orange)
![License](https://img.shields.io/github/license/YOUR_USERNAME/YOUR_REPOSITORY)
![Last Commit](https://img.shields.io/github/last-commit/YOUR_USERNAME/YOUR_REPOSITORY)

An **IoT-based automatic plant irrigation system** developed by the **IRIBOTS team** using **Arduino Uno** and **ESP8266**.

This system is designed to monitor **soil moisture levels** and automatically water plants when needed. It also supports **manual control via IoT applications**, allowing users to manage irrigation remotely.

The project supports multiple operating modes including **Offline Mode**, **Online Mode (Blynk IoT)**, and **Bluetooth Communication**.

---

# 🚀 Main Features

- ✅ Real-time soil moisture monitoring  
- ✅ Automatic irrigation based on sensor readings  
- ✅ Manual control through IoT application  
- ✅ Supports both **online and offline modes**  
- ✅ Bluetooth communication via **RX-TX**  
- ✅ Integration with **ESP8266 WiFi Module**

---

# 🔧 Hardware Components

The following hardware components are used in this project:

- **Arduino UNO**
- **ESP8266 WiFi Module**
- **Soil Moisture Sensor**
- **Relay Module**
- **Water Pump**
- **Bluetooth Module (HC-05 / HC-06)**
- **Power Supply**

---

# ⚙️ System Overview

The system works by reading the **soil moisture sensor** to determine whether the plant needs watering.

### Workflow

1. The **soil moisture sensor** reads the moisture level in the soil.
2. The microcontroller processes the sensor data.
3. If the soil is dry:
   - The **relay module activates the water pump**.
4. If the soil moisture is sufficient:
   - The **pump remains off**.
5. The system can also be controlled manually via:
   - **IoT application (Blynk)**
   - **Bluetooth communication**

---

# 📡 Operating Modes

### 1️⃣ Offline Mode
- Works without internet connection
- Automatic watering based on sensor readings

### 2️⃣ Online Mode (IoT - Blynk)
- Remote monitoring via smartphone
- Manual control of irrigation

### 3️⃣ Bluetooth Mode
- Direct communication using **HC-05 / HC-06**
- Manual control using Bluetooth-enabled devices

---

# 🧠 Technologies Used

- **Arduino**
- **ESP8266 WiFi**
- **IoT (Blynk Platform)**
- **Embedded Systems**
- **Sensor-based Automation**

---

# 📌 Use Cases

This system can be used for:

- Smart agriculture projects
- Home gardening automation
- IoT learning projects
- Smart greenhouse systems
- Embedded system experiments

---

# 👨‍💻 Developed By

**IRIBOTS Team**

Focused on developing **IoT-based smart agriculture systems** and **automation technologies**.

---

# 📄 License

This project is released under the **MIT License**.
