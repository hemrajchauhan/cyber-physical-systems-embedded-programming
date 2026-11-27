/*
 * Hardware timer configuration, interrupt handlers and timing demo.
 *
 * Timer 1: 1 Hz interrupt, clocked from the board's 32.768 kHz
 *          secondary oscillator through the SOSCO/T1CK connection.
 * Timer 2: 500 Hz interrupt (2 ms period), clocked from FCY.
 * Timer 3: free-running 16-bit counter used to time 2,000 loop passes.
 *
 * Maintainer: Hemraj Chauhan
 */

#include "timer.h"

#include <xc.h>

#include "lcd.h"
#include "led.h"

/* Instruction clock frequency used by the project. */
#define FCY                         12800000UL

/* Secondary oscillator frequency fitted to the board. */
#define SECONDARY_OSCILLATOR_HZ     32768UL

/* Timer 1: 32,768 / 256 / 128 = 1 interrupt per second. */
#define TIMER1_PRESCALER            256UL
#define TIMER1_PERIOD_TICKS         127U

/* Timer 2: 12.8 MHz / 256 / 100 = 500 Hz (2 ms). */
#define TIMER2_PRESCALER            256UL
#define TIMER2_INTERRUPT_HZ         500UL
#define TIMER2_PERIOD_TICKS         99U

#define LOOP_ITERATIONS_PER_SAMPLE  2000U

/*
 * Updated by the Timer 2 ISR. This is a 32-bit counter on a 16-bit CPU,
 * so the main loop must take a protected snapshot before reading it.
 */
static volatile unsigned long elapsed_milliseconds = 0UL;

/*
 * Configure the three timers used in this exercise.
 * Timer 1 and Timer 2 generate interrupts; Timer 3 is polled by main.
 */
void timer_initialize(void)
{
    /* Keep the timer interrupts disabled while their registers are set up. */
    IEC0bits.T1IE = 0;
    IEC0bits.T2IE = 0;

    /* Enable the 32.768 kHz secondary oscillator. */
    __builtin_write_OSCCONL(OSCCONL | 0x02);

    /* Stop timers and clear their control registers. */
    T1CON = 0;
    T2CON = 0;
    T3CON = 0;

    /* Timer 1: asynchronous external clock, 1:256 prescaler. */
    T1CONbits.TCKPS = 0b11;
    T1CONbits.TCS = 1;
    T1CONbits.TGATE = 0;
    T1CONbits.TSYNC = 0;

    /* Timer 2: internal instruction clock, 1:256 prescaler. */
    T2CONbits.TCKPS = 0b11;
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;

    /* Timer 3: internal instruction clock, no prescaling. */
    T3CONbits.TCKPS = 0b00;
    T3CONbits.TCS = 0;
    T3CONbits.TGATE = 0;

    /* Period registers contain the terminal count (N - 1). */
    PR1 = TIMER1_PERIOD_TICKS;
    PR2 = TIMER2_PERIOD_TICKS;
    PR3 = 0xFFFFU;

    /* Reset timer counters and the software uptime counter. */
    TMR1 = 0U;
    TMR2 = 0U;
    TMR3 = 0U;
    elapsed_milliseconds = 0UL;

    /* Use low interrupt priority; keep the ISRs short. */
    IPC0bits.T1IP = 1;
    IPC1bits.T2IP = 1;

    /* Clear stale interrupt flags before enabling the sources. */
    IFS0bits.T1IF = 0;
    IFS0bits.T2IF = 0;

    IEC0bits.T1IE = 1;
    IEC0bits.T2IE = 1;

    /* Start the timers after all configuration is complete. */
    T1CONbits.TON = 1;
    T2CONbits.TON = 1;
    T3CONbits.TON = 1;
}

/*
 * Read the 32-bit uptime counter consistently on the 16-bit dsPIC core.
 * Disabling only the Timer 2 interrupt protects the read; a timer event
 * occurring during this short section remains pending in T2IF.
 */
static unsigned long get_elapsed_milliseconds(void)
{
    unsigned long snapshot;
    unsigned int timer2_interrupt_was_enabled = IEC0bits.T2IE;

    IEC0bits.T2IE = 0;
    snapshot = elapsed_milliseconds;
    IEC0bits.T2IE = timer2_interrupt_was_enabled;

    return snapshot;
}

/*
 * Main-loop timing demonstration.
 * Timer 3 measures the time taken by each group of 2,000 loop iterations.
 * LCD operations occur after the timer value is captured, so LCD transfer
 * time is excluded from the reported sample.
 */
void run_timing_demo(void)
{
    unsigned int iteration_count = 0U;

    lcd_printf("Timer & Interrupts");
    lcd_locate(0, 1);
    lcd_printf("Hemraj Chauhan");

    /* Start the first measurement after the heading has been displayed. */
    TMR3 = 0U;

    for (;;)
    {
        iteration_count++;

        if (iteration_count >= LOOP_ITERATIONS_PER_SAMPLE)
        {
            unsigned int timer_ticks = TMR3;
            unsigned long uptime_ms = get_elapsed_milliseconds();
            unsigned long elapsed_us =
                ((unsigned long)timer_ticks * 1000UL) / (FCY / 1000UL);
            unsigned long uptime_minutes = uptime_ms / 60000UL;
            unsigned int uptime_seconds =
                (unsigned int)((uptime_ms / 1000UL) % 60UL);
            unsigned int uptime_subseconds =
                (unsigned int)(uptime_ms % 1000UL);

            /* The display is updated only once per measurement sample. */
            lcd_locate(0, 3);
            lcd_printf("Uptime %lu:%02u.%03u",
                       uptime_minutes,
                       uptime_seconds,
                       uptime_subseconds);

            lcd_locate(0, 5);
            lcd_printf("2,000 iterations:");

            lcd_locate(0, 6);
            lcd_printf("%u cyc = %lu us", timer_ticks, elapsed_us);

            /* LED 3 marks completion of a measurement sample. */
            LED3_LAT ^= 1U;

            /* Reset the measurement window after the display update. */
            TMR3 = 0U;
            iteration_count = 0U;
        }
    }
}

/* Timer 1: one-second heartbeat on LED 2. */
void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{
    LED2_LAT ^= 1U;
    IFS0bits.T1IF = 0;
}

/* Timer 2: 2 ms system tick; toggles LED 1 and advances uptime. */
void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T2Interrupt(void)
{
    LED1_LAT ^= 1U;
    elapsed_milliseconds += 2UL;
    IFS0bits.T2IF = 0;
}
