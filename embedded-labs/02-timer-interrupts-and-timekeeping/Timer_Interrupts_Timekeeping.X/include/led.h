/*
 * LED GPIO definitions for the Flex-UI / dsPIC33F board.
 *
 * Maintainer: Hemraj Chauhan
 */

#ifndef LED_H
#define LED_H

#include <p33Fxxxx.h>

/*
 * The five board LEDs are connected to PORTA.
 * Use TRIS bits to configure direction and LAT bits to write outputs.
 */
#define LED1_TRIS  TRISAbits.TRISA4
#define LED2_TRIS  TRISAbits.TRISA5
#define LED3_TRIS  TRISAbits.TRISA9
#define LED4_TRIS  TRISAbits.TRISA10
#define LED5_TRIS  TRISAbits.TRISA0

#define LED1_LAT   LATAbits.LATA4
#define LED2_LAT   LATAbits.LATA5
#define LED3_LAT   LATAbits.LATA9
#define LED4_LAT   LATAbits.LATA10
#define LED5_LAT   LATAbits.LATA0

void led_init(void);

#endif /* LED_H */
