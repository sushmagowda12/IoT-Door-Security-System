# IoT Door Security System

This project is an **IoT-based Door Security System** using a **NodeMCU** microcontroller. It combines an **IR sensor** and a **buzzer** to detect motion or proximity at a door and alerts users while sending the data to the cloud using **ThingSpeak** for remote monitoring.

## Features
- Detects motion or proximity using an IR sensor.
- Activates a buzzer to alert when an object is detected.
- Sends sensor data to **ThingSpeak** for real-time monitoring and storage.
- Easy to deploy and suitable for smart home security systems.

---

## Components Used
1. **NodeMCU (ESP8266)** – Wi-Fi-enabled microcontroller for IoT applications.
2. **IR Sensor** – For detecting motion or proximity.
3. **Buzzer** – For providing audible alerts.
4. **ThingSpeak** – Cloud platform for IoT data visualization.

---

## How It Works
1. The IR sensor detects motion or proximity and outputs a digital signal (HIGH or LOW).
2. The NodeMCU reads the sensor's output and activates the buzzer if motion is detected.
3. The sensor's state is sent to ThingSpeak via HTTP GET requests, where the data is visualized in real-time.
4. A delay of 15 seconds is maintained to comply with ThingSpeak's rate limit.

---

## Prerequisites
- Arduino IDE installed on your computer.
- ThingSpeak account with a configured channel.
- Wi-Fi credentials (SSID and Password).

---

## Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/sushmagowda12/IoT-Door-Security-System.git
