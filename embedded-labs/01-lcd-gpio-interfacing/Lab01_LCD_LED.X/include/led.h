/*
 * File: led.h
 * Purpose: Pin definitions and operations for the five board LEDs.
 * Target:  dsPIC33FJ256MC710 on the Amazing Ball / Flex-UI board.
 */

#ifndef LED_H
#define LED_H

#include <xc.h>
#include "types.h"

/* TRIS register bits: 0 = output, 1 = input. */
#define LED1_TRIS  TRISAbits.TRISA4
#define LED2_TRIS  TRISAbits.TRISA5
#define LED3_TRIS  TRISAbits.TRISA9
#define LED4_TRIS  TRISAbits.TRISA10
#define LED5_TRIS  TRISAbits.TRISA0

/* Output latch bits. Use LAT rather than PORT for output writes. */
#define LED1_LAT   LATAbits.LATA4
#define LED2_LAT   LATAbits.LATA5
#define LED3_LAT   LATAbits.LATA9
#define LED4_LAT   LATAbits.LATA10
#define LED5_LAT   LATAbits.LATA0

/*
 * The Nop() instruction is retained from the supplied board support code
 * between GPIO operations, as required by the original implementation.
 */
#define SETLED(bit)    do { SETBIT(bit);    Nop(); } while (0)
#define CLEARLED(bit)  do { CLEARBIT(bit);  Nop(); } while (0)
#define TOGGLELED(bit) do { TOGGLEBIT(bit); Nop(); } while (0)

/* Configure all five LED pins as outputs and initialize them LOW. */
void led_init(void);

#endif /* LED_H */
