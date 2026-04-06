/* 1 Hz flag from Timer1 — keeps loop non-blocking vs delay() everywhere */
#include <Arduino.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "Timer1Tick.h"

static volatile uint8_t s_pending_1s;

ISR(TIMER1_COMPA_vect)
{
    s_pending_1s = 1u; // ISR stays tiny on purpose
}

void Timer1_init_1Hz_tick(void)
{
    TCCR1A = 0u;
    // CTC + /1024, OCR1A chosen so it's ~1s on 16MHz (close enough)
    TCCR1B = (uint8_t)((1u << WGM12) | (1u << CS12) | (1u << CS10));
    OCR1A = 15624u;
    TIMSK1 = (uint8_t)(1u << OCIE1A);
    TCNT1 = 0u;
}

uint8_t Timer1_consume_1s_tick(void)
{
    uint8_t oldSREG = SREG;
    cli(); // clear flag atomically
    uint8_t v = s_pending_1s;
    s_pending_1s = 0u;
    SREG = oldSREG;
    return v;
}
