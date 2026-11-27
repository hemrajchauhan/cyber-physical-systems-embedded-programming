/*
 * Project: LCD and GPIO Interfacing
 * Target:  Microchip dsPIC33FJ256MC710
 * Board:   Amazing Ball / Flex-UI embedded development board
 * Maintainer: Hemraj Chauhan
 *
 * Description:
 *   Initializes the LCD and five GPIO-connected LEDs. The application
 *   displays project information and a counter on the LCD while presenting
 *   the same counter as a five-bit binary value on the LEDs. The counter
 *   advances every 500 ms and wraps from 31 back to 0.
 */

#include <xc.h>

/* Define the instruction-cycle frequency before including libpic30.h. */
#define FCY 12800000UL
#include <libpic30.h>

#include "lcd.h"
#include "led.h"

/* Device configuration bits. */
#pragma config FNOSC = PRIPLL   /* Primary oscillator with PLL. */
#pragma config POSCMD = XT      /* Primary oscillator uses an XT crystal. */
#pragma config FWDTEN = OFF     /* Watchdog timer disabled. */

/* Application configuration. */
#define COUNTER_VALUE_COUNT        32u
#define COUNTER_UPDATE_INTERVAL_MS 500u
#define COUNTER_LCD_ROW            4u

/* These functions are private to this application module. */
static void display_project_info(void);
static void display_counter(unsigned int counter_value);
static void update_led_display(unsigned int counter_value);

int main(void)
{
    unsigned int counter_value = 0u;

    /* Initialize the peripherals used by this application. */
    led_init();
    lcd_initialize();
    lcd_clear();

    display_project_info();

    /* Continuously display the counter on the LCD and LEDs. */
    while (1)
    {
        display_counter(counter_value);
        update_led_display(counter_value);

        /* Keep each value visible before advancing the counter. */
        __delay_ms(COUNTER_UPDATE_INTERVAL_MS);

        /* Five LEDs represent 32 values: 0 through 31. */
        counter_value++;
        if (counter_value >= COUNTER_VALUE_COUNT)
        {
            counter_value = 0u;
        }
    }

    /* The application runs continuously; execution does not normally reach here. */
    return 0;
}

/* Display the maintainer and project title without personal group information. */
static void display_project_info(void)
{
    lcd_locate(0, 0);
    lcd_printf("Hemraj Chauhan");

    lcd_locate(0, 1);
    lcd_printf("LCD and GPIO Demo");
}

/* Display the current counter value on the configured LCD row. */
static void display_counter(unsigned int counter_value)
{
    lcd_locate(0, COUNTER_LCD_ROW);
    lcd_printf("Counter: %2u", counter_value);
}

/*
 * Display the counter as a five-bit binary value.
 *
 * LED1 is connected to bit 4 (MSB), and LED5 is connected to bit 0 (LSB).
 * For example, decimal 18 is binary 10010, so LED1 and LED4 are illuminated.
 */
static void update_led_display(unsigned int counter_value)
{
    /* LED1 represents bit 4 (the most significant bit). */
    if ((counter_value & (1u << 4)) != 0u)
    {
        SETLED(LED1_LAT);
    }
    else
    {
        CLEARLED(LED1_LAT);
    }

    /* LED2 represents bit 3. */
    if ((counter_value & (1u << 3)) != 0u)
    {
        SETLED(LED2_LAT);
    }
    else
    {
        CLEARLED(LED2_LAT);
    }

    /* LED3 represents bit 2. */
    if ((counter_value & (1u << 2)) != 0u)
    {
        SETLED(LED3_LAT);
    }
    else
    {
        CLEARLED(LED3_LAT);
    }

    /* LED4 represents bit 1. */
    if ((counter_value & (1u << 1)) != 0u)
    {
        SETLED(LED4_LAT);
    }
    else
    {
        CLEARLED(LED4_LAT);
    }

    /* LED5 represents bit 0 (the least significant bit). */
    if ((counter_value & (1u << 0)) != 0u)
    {
        SETLED(LED5_LAT);
    }
    else
    {
        CLEARLED(LED5_LAT);
    }
}
