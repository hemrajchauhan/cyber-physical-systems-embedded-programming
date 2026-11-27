/*
 * File: led.c
 * Purpose: GPIO initialization for the five board LEDs.
 */

#include "led.h"

/*
 * Configure all five LED pins as digital outputs and start with every LED off.
 * The LAT registers are cleared before the TRIS bits are changed to outputs,
 * avoiding an unintended HIGH level when the pins become active outputs.
 */
void led_init(void)
{
    /* Preload LOW output values. */
    CLEARLED(LED1_LAT);
    CLEARLED(LED2_LAT);
    CLEARLED(LED3_LAT);
    CLEARLED(LED4_LAT);
    CLEARLED(LED5_LAT);

    /* A TRIS bit of 0 configures the corresponding pin as an output. */
    CLEARBIT(LED1_TRIS);
    Nop();
    CLEARBIT(LED2_TRIS);
    Nop();
    CLEARBIT(LED3_TRIS);
    Nop();
    CLEARBIT(LED4_TRIS);
    Nop();
    CLEARBIT(LED5_TRIS);
    Nop();
}
