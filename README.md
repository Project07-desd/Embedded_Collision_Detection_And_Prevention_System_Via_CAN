# Collision Detection and Prevention System

This project implements a **collision detection and prevention system** using various hardware components including an **HC-SR04 ultrasonic sensor**, **STM32F407VGT6 microcontroller**, **SN65HVD230 CAN Bus Transceiver**, and **ESP32** to send data to Amazon Web Services (AWS) for further processing.

## Overview

The system works by using the **HC-SR04 ultrasonic sensor** to measure the distance to obstacles in real-time. This data is then sent to an **STM32F407VGT6 microcontroller** for processing. The STM32F407VGT6 will communicate this information over the **CAN Bus** using an **SN65HVD230 CAN Transceiver**. A second **STM32F407VGT6** is used to forward the data to AWS via **ESP32**, where it can be processed further.

## Hardware Components

- **HC-SR04 Ultrasonic Sensor**: Measures the distance to obstacles in the environment.
- **STM32F407VGT6 Microcontroller**: Processes the distance data and handles the communication between different components.
- **SN65HVD230 CAN Bus Transceiver**: Facilitates communication over the CAN network between microcontrollers.
- **ESP32**: Sends data to Amazon Web Services (AWS) for further processing.

## Workflow

1. **Distance Measurement**: The HC-SR04 sensor detects obstacles and measures the distance.
2. **Data Processing**: The first STM32F407VGT6 microcontroller processes the data and sends it to the CAN bus.
3. **CAN Bus Communication**: The SN65HVD230 transceiver transmits the data over the CAN bus to a second STM32F407VGT6.
4. **Data Forwarding to AWS**: The second STM32F407VGT6, using an ESP32, forwards the data to AWS for further processing.

## Features

- **Real-Time Collision Detection**: Continuously monitors the distance and detects any potential collisions.
- **CAN Bus Communication**: Reliable communication between microcontrollers over a CAN bus network.
- **Cloud Integration**: Sends data to AWS for further processing.

## Installation

### Prerequisites

- **STM32CubeIDE** for STM32F407VGT6 programming
- **Arduino IDE** for ESP32 programming
- **AWS IoT Core Account** for cloud integration

### Setting Up Hardware

1. **HC-SR04 Ultrasonic Sensor**:
   - Connect the **Trig** pin to a GPIO pin on the STM32F407VGT6.
   - Connect the **Echo** pin to another GPIO pin on the STM32F407VGT6.
   
2. **SN65HVD230 CAN Transceiver**:
   - Connect the CAN transceiver to the STM32F407VGT6 for CAN bus communication.

3. **ESP32**:
   - Configure the ESP32 to send data to AWS IoT Core via MQTT or HTTP.

### Software Setup

1. **Install STM32CubeIDE** and create a new project for STM32F407VGT6.
2. **Install the CAN Bus Library** and configure the CAN interface.
3. **Program the STM32F407VGT6** with the collision detection and CAN communication code.
4. **Install the ESP32 Board in Arduino IDE** and program it to send data to AWS IoT Core.

## AWS IoT Core Setup

1. Create an **IoT Thing** in AWS IoT Core.
2. Set up the **MQTT** protocol for communication.
3. Create and attach an **IoT policy** to allow publishing data from the ESP32.

## Directory Structure

```plaintext
/
├── firmware/
│   ├── stm32f407vgt6/
│   │   └── collision_detection.c
│   ├── can_bus/
│   │   └── can_communication.c
│   └── esp32/
│       └── aws_mqtt.c
├── docs/
│   └── project_overview.md
├── schematics/
│   └── circuit_diagram.png
└── README.md
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
