# Timer Interrupts and Timekeeping

**Embedded C · dsPIC33F · Hardware Timers · Interrupt Service Routines**

A microcontroller programming project demonstrating hardware timer
configuration, periodic interrupts, GPIO control, software timekeeping
and main-loop execution-time measurement on the Flex-UI development board.

**Portfolio maintainer:** Hemraj Chauhan

## Overview

The application uses three hardware timers:

- **Timer 1** uses the board's 32.768 kHz secondary oscillator to generate
  a one-second interrupt. Its ISR toggles LED 2 as a heartbeat.
- **Timer 2** uses the 12.8 MHz instruction clock to generate a 2 ms
  interrupt. Its ISR increments a 32-bit uptime counter and toggles LED 1.
- **Timer 3** is a free-running 16-bit counter. The main loop reads it after
  every 2,000 iterations to estimate execution time and toggles LED 3.

The LCD displays uptime and the Timer 3 measurement. LCD operations are
performed in the main loop, not inside an interrupt service routine.

## Hardware and configuration

| Item | Configuration |
|---|---|
| Microcontroller | Microchip dsPIC33FJ256MC710 |
| Instruction clock (`FCY`) | 12.8 MHz |
| Timer 1 clock | 32.768 kHz secondary oscillator (SOSC) |
| Timer 1 prescaler | 1:256 |
| Timer 1 period register | 127 |
| Timer 1 interrupt rate | 1 Hz |
| Timer 2 clock | Instruction clock (`FCY`) |
| Timer 2 prescaler | 1:256 |
| Timer 2 period register | 99 |
| Timer 2 interrupt rate | 500 Hz (2 ms) |
| Timer 3 clock | Instruction clock (`FCY`) |
| Timer 3 prescaler | 1:1 |
| Timer 3 period register | 65,535 |
| Display | Flex-UI LCD |

### LED mapping

| LED | dsPIC pin | Behaviour |
|---|---|---|
| LED 1 | RA4 | Toggles every 2 ms in the Timer 2 ISR |
| LED 2 | RA5 | Toggles every second in the Timer 1 ISR |
| LED 3 | RA9 | Toggles after each 2,000-iteration measurement |
| LED 4 | RA10 | Configured as output; unused in this application |
| LED 5 | RA0 | Configured as output; unused in this application |

## Timer calculations

The period register stores the terminal count, so the number of timer
counts per period is `PRx + 1`.

### Timer 1 — one-second interrupt

`32,768 / 256 / (127 + 1) = 1 Hz`

The secondary oscillator is enabled through `LPOSCEN`. Timer 1 is configured
for asynchronous external-clock operation; on this device the SOSCO/T1CK
function is shared on pin RC14.

### Timer 2 — two-millisecond interrupt

`12,800,000 / 256 / (99 + 1) = 500 Hz`

A 500 Hz interrupt corresponds to a 2 ms interval. The ISR advances the
uptime counter by 2 ms per interrupt. The main loop briefly disables the
Timer 2 interrupt while taking a consistent snapshot of the 32-bit counter;
a timer interrupt flag that becomes pending during this short section is
serviced after the interrupt is re-enabled.

### Timer 3 — main-loop timing

Timer 3 increments at 12.8 MHz with no prescaler. Its 16-bit period gives
65,536 counts before rollover:

`65,536 / 12,800,000 = 5.12 ms`

**Measurement limitation:** The reported sample is accurate only if the
2,000 loop iterations complete in less than 5.12 ms. If the interval is
longer, Timer 3 wraps and the reported value underestimates the duration.
Timer 3 continues counting while Timer 1 and Timer 2 interrupts execute,
so interrupt execution time is included in the measurement. LCD transfer
time is excluded because the counter is captured before the display update.

## Software structure

```text
02-timer-interrupts-and-timekeeping/
├── README.md
├── .gitignore
└── Timer_Interrupts_Timekeeping.X/
    ├── Makefile
    ├── include/
    │   ├── timer.h
    │   ├── lcd.h
    │   ├── led.h
    │   └── types.h
    ├── lib/
    │   └── libLCD.a
    ├── nbproject/
    │   ├── configurations.xml
    │   ├── Makefile-default.mk
    │   ├── Makefile-impl.mk
    │   ├── Makefile-variables.mk
    │   └── project.xml
    └── src/
        ├── main.c
        ├── timer.c
        └── led.c
```

## Development environment

The MPLAB X project targets `dsPIC33FJ256MC710` and retains the original
XC16 toolchain configuration (XC16 1.36). Open the
`Timer_Interrupts_Timekeeping.X` project in MPLAB X IDE and select an
installed compatible XC16 compiler if prompted.

The project includes the course-provided `libLCD.a` library and its
corresponding `lcd.h` interface. The LCD header retains its upstream
attribution. Confirm that the precompiled library may be redistributed
before publishing this repository publicly.

## Build and verification

1. Open `Timer_Interrupts_Timekeeping.X` in MPLAB X IDE.
2. Confirm the selected device is `dsPIC33FJ256MC710`.
3. Confirm that XC16 and the required device pack are installed.
4. Build the project.
5. Connect the compatible Flex-UI board and program the device.
6. Observe LED 1, LED 2 and LED 3 and inspect the LCD output.

The source has been reviewed and reorganized, but compilation and physical
board behaviour still need to be verified in the target MPLAB X / XC16
environment before describing the project as hardware-tested.

## Code organization

- `src/main.c`: device configuration and application startup.
- `src/timer.c`: timer configuration, uptime handling and interrupt service routines.
- `src/led.c` and `include/led.h`: LED GPIO initialization and pin definitions.
- `include/timer.h`: timer demonstration interface.
- `include/lcd.h` and `lib/libLCD.a`: course-provided LCD dependency.

## Attribution

Application code documentation and portfolio maintenance: **Hemraj Chauhan**.

The LCD interface header retains its original upstream adaptation notice.
Course-provided and third-party components should retain their applicable
notices and licensing terms.
