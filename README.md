# ESP32 Learning Projects

A collection of practical ESP32 projects created while learning embedded systems programming, hardware peripherals, interrupts, timers, sensors, displays, PWM control, and FreeRTOS.

The purpose of this repository is to gain hands-on experience with real-world embedded development using ESP32 and C++.

---

## Technologies Used

- ESP32
- C++
- Arduino Framework
- GPIO
- ADC (Analog-to-Digital Converter)
- PWM (LEDC)
- Hardware Timers
- Interrupts (ISR)
- FreeRTOS
- Queues
- UART (Serial Communication)
- DHT11 Temperature & Humidity Sensor
- TM1637 4-Digit Display
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Piezo Buzzer

---

# Projects

## 1. Alarm System

A simple motion detection alarm system.

### Features
- Motion detection using external interrupt
- LED alarm indication
- Piezo buzzer alarm
- Automatic alarm shutdown after a timeout
- Non-blocking timing using `millis()`

### Concepts Practiced
- GPIO
- Interrupts (ISR)
- Event-driven programming
- Timing with `millis()`

---

## 2. Brightness Control

Controls LED brightness using a potentiometer.

### Features
- Analog input reading
- ADC value mapping
- PWM brightness control
- Real-time monitoring through Serial Monitor

### Concepts Practiced
- ADC
- PWM (LEDC)
- Signal scaling and mapping
- UART communication

---

## 3. Radar Scanner

A simple radar simulation using a servo motor and ultrasonic distance sensor.

### Features
- Servo sweep from 0° to 180°
- Distance measurement with HC-SR04
- Object detection within a configurable range
- Angle and distance reporting via Serial Monitor

### Concepts Practiced
- Servo control
- Ultrasonic sensing
- PWM
- Sensor integration
- Real-time measurements

---

## 4. Thermometer With Display

Displays temperature and humidity from a DHT11 sensor on a TM1637 display.

### Features
- Periodic sensor readings
- Temperature display
- Humidity display
- Hardware timer interrupt
- Serial logging

### Concepts Practiced
- Hardware Timers
- Interrupt Service Routines (ISR)
- Sensor communication
- Display control
- Non-blocking embedded design

---

## 5. Traffic Light Controller

A traffic light simulation with pedestrian crossing support.

### Features
- Red, yellow, and green light sequencing
- Pedestrian button interrupt
- State transitions based on timing
- Event-driven control logic

### Concepts Practiced
- GPIO
- Interrupts
- Finite state behavior
- Timing with `millis()`

---

## 6. FreeRTOS Temperature Monitoring Station

A multitasking application using FreeRTOS.

### Features
- Independent sensor task
- Independent display task
- Independent serial output task
- Queue-based communication between tasks
- Multi-core task execution

### Concepts Practiced
- FreeRTOS
- Tasks
- Queues
- Inter-task communication
- Concurrent programming
- Multi-core ESP32 architecture

---

# Learning Goals

This repository was created to practice and understand:

- Embedded C++ programming
- ESP32 peripherals
- Interrupts and ISR design
- Hardware timers
- ADC and PWM
- Sensor integration
- Display control
- UART communication
- Real-time programming
- FreeRTOS multitasking
- Queue-based data exchange
- Embedded software architecture

---

# Hardware Used

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- TM1637 4-Digit Display
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Potentiometer
- LEDs
- Push Button
- Piezo Buzzer

---

# Author

Denys Burduzhan

Learning Embedded Systems, ESP32, FreeRTOS, and Real-Time Programming.
