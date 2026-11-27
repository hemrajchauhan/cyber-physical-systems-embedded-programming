/*
 * LED GPIO initialization.
 *
 * Maintainer: Hemraj Chauhan
 */

#include "led.h"

void led_init(void)
{
    /*
     * Set the output latches low before switching the pins to output
     * mode. This avoids briefly driving an undefined output level.
     */
    LED1_LAT = 0;
    LED2_LAT = 0;
    LED3_LAT = 0;
    LED4_LAT = 0;
    LED5_LAT = 0;

    /* Configure all five LED pins as digital outputs. */
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
}
