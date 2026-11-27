# dsPIC33F Cyber-Physical Systems Engineering

**Embedded C Programming · Microcontroller Interfacing · Real-Time Systems · Signal Processing**

A collection of embedded software projects developed as part of the *Concepts and Software Design for Cyber-Physical Systems* course.

The projects use the Microchip dsPIC33F microcontroller and the Amazing Ball embedded development board to explore low-level programming, peripheral interfacing, hardware–software integration, real-time behaviour and signal processing.

<p align="center">
  <img
    src="https://github.com/user-attachments/assets/dcd1547c-4bf3-4877-aa1e-8fd6688562e0"
    alt="Amazing Ball Embedded Development Board"
    width="750"
  >
  <br>
  <em>Amazing Ball – dsPIC33F Embedded Development Board</em>
</p>

## Overview

This repository documents practical work involving the design, implementation and analysis of embedded software for a microcontroller-based cyber-physical system.

The projects progressively explore fundamental embedded engineering concepts, including:

- Embedded C programming and low-level hardware access
- GPIO configuration and digital interfacing
- LCD interfacing and display control
- Hardware timers and interrupt-driven programming
- SPI communication and DAC interfacing
- Analog signal generation and processing
- Real-time execution and timing considerations
- Hardware–software integration

The repository also includes a final project developed for the Amazing Ball embedded development board.

## Hardware Platform

### Amazing Ball Embedded Development Board

The projects are developed for an embedded platform built around the **Microchip 16-bit dsPIC33F microcontroller**.

| Specification | Description |
|---|---|
| Microcontroller | Microchip dsPIC33F, 16-bit |
| Clock frequency | 12.8 MHz |
| Flash program memory | 259 KB |
| SRAM | 30,720 bytes |
| LCD | 128 × 64 pixels |
| Touchscreen | 4-wire |
| Analog interfaces | Digital-to-Analog Converter (DAC) and Analog-to-Digital Converter (ADC) |
| Actuators | Servo motors |
| Communication | Serial port |
| User input | Joystick port |

The board provides a combination of processing, sensing, display, communication and actuation capabilities for developing embedded applications.

## Projects

The repository is organized by engineering topic rather than assignment numbering. Each project focuses on a specific area of embedded systems development.

### 01. LCD and GPIO Interfacing

**Directory:** `embedded-labs/01-lcd-gpio-interfacing/`

Focus: Digital input/output and display interfacing.

Topics:
- GPIO configuration and digital output control
- LCD initialization and display operations
- LED control and binary representation
- Bitwise operations and bit manipulation
- Microcontroller peripheral configuration

### 02. Timer Interrupts and Timekeeping

**Directory:** `embedded-labs/02-timer-interrupts-and-timekeeping/`

Focus: Hardware timers and interrupt-driven execution.

Topics:
- Hardware timer configuration
- Interrupt service routines (ISRs)
- Timer periods and prescaler calculations
- Periodic event generation
- Timekeeping and elapsed-time measurement
- LCD-based time display

### 03. SPI and Digital-to-Analog Conversion

**Directory:** `embedded-labs/03-spi-digital-to-analog-conversion/`

Focus: Serial peripheral communication and analog output generation.

Topics:
- Digital-to-Analog Converter (DAC) interfacing
- Software SPI communication
- 16-bit DAC command transmission
- Voltage output configuration
- Timer-based timing mechanisms
- Hardware–software interfacing

### 04. Waveform Generation and Signal Analysis

**Directory:** `embedded-labs/04-waveform-generation-and-signal-analysis/`

Focus: Embedded signal generation and digital signal processing.

Topics:
- Sine-wave generation using a DAC
- Timer 3 interrupt-driven sampling
- Sampling frequency and timer configuration
- Analog signal generation
- LED toggling within periodic interrupts
- MATLAB signal processing
- Butterworth low-pass filtering
- Fast Fourier Transform (FFT)
- Frequency estimation of harmonic signals

### 05. [Project Title]

**Directory:** `embedded-labs/05-[technical-topic]/`

Details and technical objectives will be documented after the project implementation and specification have been reviewed.

### 06. [Project Title]

**Directory:** `embedded-labs/06-[technical-topic]/`

Details and technical objectives will be documented after the project implementation and specification have been reviewed.

## Final Project: Amazing Ball Embedded System

**Directory:** `final-project/amazing-ball-embedded-system/`

The final project brings together concepts explored throughout the course in an application developed for the Amazing Ball embedded development board.

This section will document:

- System architecture and software design
- Embedded application structure
- Peripheral configuration and integration
- Hardware interaction and control logic
- Real-time behaviour and timing
- Sensor and actuator interfacing
- Implementation details and design decisions
- Demonstrations and experimental results

Further technical details will be added as the final implementation develops.

## Software and Development Tools

The projects use the following development technologies where applicable:

| Tool / Technology | Purpose |
|---|---|
| C | Embedded software development |
| MPLAB X IDE | Microcontroller project development |
| Microchip XC16 | C compiler for dsPIC microcontrollers |
| MATLAB | Signal processing and frequency analysis |
| Git | Version control |
| GitHub | Source code management and project documentation |

## Repository Structure

```text
dspic33f-cyber-physical-systems/
│
├── README.md
├── .gitignore
├── LICENSE
│
├── embedded-labs/
│   ├── 01-lcd-gpio-interfacing/
│   ├── 02-timer-interrupts-and-timekeeping/
│   ├── 03-spi-digital-to-analog-conversion/
│   ├── 04-waveform-generation-and-signal-analysis/
│   ├── 05-[technical-topic]/
│   └── 06-[technical-topic]/
│
├── final-project/
│   └── amazing-ball-embedded-system/
│
└── docs/
    ├── hardware-overview/
    ├── development-environment/
    └── images/
```

Each project directory contains its relevant source code, header files, development configuration and project-specific documentation.

## Engineering Focus

The projects provide practical experience in the following areas:

| Engineering Area | Concepts |
|---|---|
| Embedded Programming | C, pointers, memory, bitwise operations |
| Microcontroller Architecture | Registers, GPIO, peripheral configuration |
| Real-Time Systems | Timers, interrupts, periodic execution |
| Hardware Interfacing | LCD, SPI, DAC, ADC |
| Signal Processing | Sampling, filtering, FFT, frequency estimation |
| Software Design | Modular programming, code organization, documentation |
| System Integration | Hardware–software interaction and peripheral integration |

## Documentation and Code Quality

The source code is being organized and reviewed to improve maintainability and readability.

The documentation aims to explain:

- The purpose and operation of each software module
- Hardware dependencies and peripheral configurations
- Important register settings and timing calculations
- Interrupt behaviour and execution flow
- Design decisions and implementation considerations

The original course requirements and the actual implementation are kept distinguishable from subsequent code improvements.

## Acknowledgements

Developed as part of the *Concepts and Software Design for Cyber-Physical Systems* course.

Hardware platform: Amazing Ball embedded development board.

Course-provided starter code and third-party libraries will be acknowledged in their respective project documentation.

## License

License and redistribution information will be specified after reviewing the licensing conditions of the course-provided code and external libraries.

---

**Focus:** Embedded Software Engineering · Cyber-Physical Systems · Microcontroller Programming · Hardware–Software Integration
