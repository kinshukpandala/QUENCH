# QUENCH - ESP32 Firmware

## Overview

This repo contains the firmware for QUENCH a Robotics Water Kiosk, running on an ESP32 microcontroller.

It implements a **real-time,multitasking system** to manage:

- Keyboard Input
- TFT Display (SPI)
- QR code generation for UPI Payments
- Motor Control
- Sensor monitoring (flow, water level)
- MQTT communication with Raspi backend

This system is designed for **reliability**, **modularity**, and **remote monitoring**.

## Features

- **Peripheral Interfaces:**
  - SPI: TFT display (ILI9341)
  - I2C: Optional sensors (e.g. weight, level sensors)
  - UART: Communication with Raspi
- **MQTT interaction:** Publishes sensor/actuator status and payment events to Raspi dashboard custom built
- **Sensor & Actuator Status Monitoring:** Real-time detection of device errors with alerts and MQTT notifications.
- **QR-based UPI Payments:** Generates dynamic QR codes for payments.

## Hardware Used:

- **ESP32 Dev Board**
- **ILI9341 TFT Display**
- **Servo Motor**
- **Water level Sensor**
- **Wifi for MQTT communication**

## Currently Working on:

- Converting the code based into a real time embedded system using **FreeRTOS**.
- Improving the connectivity and sensor status accuracy using **MQTT protocol**.
