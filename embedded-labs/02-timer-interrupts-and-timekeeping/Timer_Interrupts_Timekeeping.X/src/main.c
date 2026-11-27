/*
 * Application entry point.
 *
 * Initializes the LCD, GPIO and hardware timers before starting the
 * timer/interrupt demonstration.
 *
 * Maintainer: Hemraj Chauhan
 */

#include <xc.h>

#include "lcd.h"
#include "led.h"
#include "timer.h"

/* Device oscillator configuration: primary crystal with PLL. */
#pragma config FNOSC = PRIPLL
#pragma config POSCMD = XT
#pragma config OSCIOFNC = ON
#pragma config FWDTEN = OFF

int main(void)
{
    lcd_initialize();
    led_init();

    lcd_clear();
    lcd_locate(0, 0);

    timer_initialize();
    run_timing_demo();

    /* The demonstration is intentionally continuous. */
    for (;;)
    {
        /* Periodic work is performed by the configured timer ISRs. */
    }
}
