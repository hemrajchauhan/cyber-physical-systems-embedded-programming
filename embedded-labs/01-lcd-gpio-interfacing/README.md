# LCD and GPIO Interfacing

**Maintainer:** Hemraj Chauhan  
**Platform:** Amazing Ball / Flex-UI development board  
**Microcontroller:** Microchip dsPIC33FJ256MC710  
**Language:** Embedded C  
**IDE / toolchain recorded in the supplied project:** MPLAB X IDE 5.10 / XC16 1.36

## Overview

This project demonstrates basic digital input/output and LCD interfacing on the dsPIC33FJ256MC710. It initializes the LCD and five board LEDs, displays the maintainer name and project title, and continuously counts from 0 to 31. The counter is shown numerically on the LCD and simultaneously as a five-bit binary value on the LEDs.

## Functionality

- Initializes and clears the LCD.
- Displays the maintainer name and project title.
- Displays the current counter value on the LCD.
- Maps the five counter bits to five GPIO-connected LEDs.
- Advances the counter every 500 ms and wraps from 31 to 0.

## LED-to-bit mapping

| LED | dsPIC pin | Counter bit | Weight |
|---|---|---:|---:|
| LED1 | RA4 | 4 (MSB) | 16 |
| LED2 | RA5 | 3 | 8 |
| LED3 | RA9 | 2 | 4 |
| LED4 | RA10 | 1 | 2 |
| LED5 | RA0 | 0 (LSB) | 1 |

For example, decimal `18` is binary `10010`, so LED1 and LED4 are ON while the other LEDs are OFF.

## Implementation

### Application flow

1. Initialize the five LED GPIO pins and set their output latches LOW.
2. Initialize and clear the LCD.
3. Display the project information.
4. Display the current counter value on the LCD.
5. Update the five LEDs according to the counter bits.
6. Wait for the configured update interval, increment the counter and wrap it to zero after 31.

### GPIO output handling

The implementation writes LED states through the `LAT` registers rather than the `PORT` registers. The output latches are initialized LOW before the corresponding `TRIS` bits configure the pins as outputs. On the dsPIC, a `TRIS` bit value of `0` selects output mode.

### Counter and timing

Five LEDs encode a range of 32 values (`2^5`), from 0 to 31. The application waits 500 ms between displayed values using `__delay_ms()` from the Microchip `libpic30` support library. The project defines `FCY` as 12.8 MHz, matching the original project configuration; the actual instruction-cycle frequency must match the target board clock configuration for the delay to be accurate.

## Software structure

```text
Lab01_LCD_LED.X/
├── include/
│   ├── lcd.h       # LCD interface supplied with the course project
│   ├── led.h       # LED pin definitions and interface
│   └── types.h     # Compatibility types and bit-operation macros
├── lib/
│   └── libLCD.a    # Precompiled LCD library supplied with the course project
├── nbproject/      # MPLAB X project configuration
├── src/
│   ├── led.c       # LED GPIO initialization
│   └── main.c      # Application flow, LCD output and binary counter
└── Makefile
```

## Build environment

The supplied MPLAB X project identifies the target as `dsPIC33FJ256MC710` and records MPLAB X IDE 5.10 and XC16 compiler 1.36. A compatible MPLAB X installation, XC16 toolchain and device support pack are required to build the project.

1. Open `Lab01_LCD_LED.X` in MPLAB X IDE.
2. If prompted, install or select the device support pack for the dsPIC33F-GP-MC family.
3. Select the XC16 toolchain. The archived project was configured with XC16 1.36; a different compiler version may require project-setting updates.
4. Build the `default` configuration.
5. Connect a compatible development board and programmer/debugger to verify the hardware behaviour.

Machine-specific MPLAB `private` settings and generated build outputs are excluded. MPLAB X may regenerate local project settings when the project is opened.

## Verification status

The source has been reviewed and refactored for readability, removal of group-specific information, and GPIO output-latch usage. The counter rollover logic has also been made explicit. It has **not been compiled or tested on physical hardware as part of this packaging step**. Build and board verification should be completed with the required Microchip toolchain and hardware.

## Attribution and third-party components

`lcd.h` and `lib/libLCD.a` are supplied with the original course project. The header identifies the LCD interface as an adaptation of the SparkFun Serial Graphic LCD library and attributes the adaptation to N. Edwards (2011). The precompiled library's source and separate license text were not included in the supplied archive. Check the course redistribution requirements and the applicable upstream license before publishing these files in a public repository.
