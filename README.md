# Li-Fi Hazard Detection Prototype

## Overview

The Li-Fi Hazard Detection Prototype is a project developed for the CSE211: Introduction to Embedded Systems course at Ain Shams University. The system is designed to detect hazards using a combination of sensors and communicate danger alerts through Li-Fi (Light Fidelity) technology. The prototype includes a sender platform (TM4C123GH6PM microcontroller) connected to sensors (Fume Sensor, Ultrasonic Sensor, and Magnetic Sensor) and a receiver platform that triggers alarms and sends notifications to a mobile app via Bluetooth.

## Features

- **Sensor Integration:** The sender platform is equipped with Fume, Ultrasonic, and Magnetic sensors to detect various hazards such as fire, door intrusion, and more.
  
- **Li-Fi Communication:** Utilizes Li-Fi technology to transmit data at high speeds over visible light, ensuring secure and interference-free communication.

- **Alarm System:** When a hazard is detected, the system activates alarms, including a flashing lamp, buzzer, and an LCD display showing a corresponding message (e.g., "Fire Alert").

- **Mobile App Integration:** Notifications are sent to a mobile app via Bluetooth, providing real-time alerts to users.

## Project Structure

The project is structured into sender and receiver platforms, each with specific functionalities. The sender platform manages hazard detection using sensors and transmits data through Li-Fi, while the receiver platform processes incoming data, triggers alarms, and communicates with the mobile app.

## Implementation

The source code files for both sender and receiver platforms are provided in their folders respectively. The implementation includes detailed wiring diagrams and circuit layouts.

**Note:** This README file provides a concise overview. Refer to the source files for more detailed information.
