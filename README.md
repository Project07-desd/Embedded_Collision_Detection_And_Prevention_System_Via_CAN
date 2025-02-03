# Collision Detection and Prevention System 🚗⚠️

This project implements a **collision detection and prevention system** utilizing an **HC-SR04 ultrasonic sensor**, **STM32F407VGT6 microcontroller**, **SN65HVD230 CAN Bus Transceiver**, and **ESP32** to send data to **Amazon Web Services (AWS)** for further processing. ☁️

## Overview

The system uses the **HC-SR04 ultrasonic sensor** to measure distance to obstacles in real-time. 📏 This data is processed by the **STM32F407VGT6**, then transmitted via **CAN Bus** using the **SN65HVD230 CAN Transceiver**. 🔄 A second **STM32F407VGT6**, connected to an **ESP32**, forwards the data to **AWS** for further analysis. 🌐

## Hardware Components

- **HC-SR04 Ultrasonic Sensor** 📡: Measures the distance to nearby obstacles.
- **STM32F407VGT6 Microcontroller** 💻: Processes the sensor data and manages communication.
- **SN65HVD230 CAN Transceiver** 🔌: Provides CAN bus communication between microcontrollers.
- **ESP32** 🌍: Forwards data to **AWS IoT Core** for further processing.

## Workflow

1. **Distance Measurement** 📏: The **HC-SR04** detects obstacles and measures the distance.
2. **Data Processing** 🧠: The first **STM32F407VGT6** processes the distance data.
3. **CAN Bus Communication** 🔄: Data is transmitted over CAN Bus using the **SN65HVD230**.
4. **Data Forwarding to AWS** ☁️: The second **STM32F407VGT6**, using the **ESP32**, sends data to **AWS**.

## Features

- **Real-Time Collision Detection** 🚗💥: Continuously detects potential obstacles.
- **Reliable CAN Bus Communication** 🔗: Transmits data efficiently between microcontrollers.
- **Cloud Integration** ☁️: Sends data to **AWS** for further processing.

## Installation

### Prerequisites

- **STM32CubeIDE** 💻 for STM32F407VGT6 development
- **Arduino IDE** 🖥️ for ESP32 programming
- **AWS IoT Core Account** 🌐 for cloud integration

### Hardware Setup

1. **HC-SR04 Ultrasonic Sensor** 📡:
   - Connect **Trig** and **Echo** pins to **STM32F407VGT6** GPIO pins.
   
2. **SN65HVD230 CAN Transceiver** 🔌:
   - Interface with the STM32F407VGT6 for CAN communication.

3. **ESP32** 🌍:
   - Configure to send data to **AWS IoT Core** via MQTT or HTTP.

### Software Setup

1. **STM32CubeIDE** 💻: Create a project for the **STM32F407VGT6**.
2. **CAN Bus Library** 🔧: Configure CAN interface for communication.
3. **Program the Microcontroller** 💾: Implement collision detection and data transmission.
4. **ESP32 Setup** 🌐: Use **Arduino IDE** to configure the ESP32 for AWS communication.

## AWS IoT Core Setup

1. Create an **IoT Thing** 🛠️ in **AWS IoT Core**.
2. Set up **MQTT** 📨 communication.
3. Create an **IoT policy** 📜 to allow data publishing.
