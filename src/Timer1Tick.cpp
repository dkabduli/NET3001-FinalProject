/* Timer1 compare A — fires about once per second, we use it instead of delay() in loop */
#include <Arduino.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "Timer1Tick.h"

static volatile uint8_t s_pending_1s;

ISR(TIMER1_COMPA_vect)
{
    s_pending_1s = 1u; /* keep isr stupid short, main does the work */
}

void Timer1_init_1Hz_tick(void)
{
    TCCR1A = 0u;
    /* CTC mode, clk/1024, OCR1A picked so compare match ~= 1s at 16MHz (datasheet math) */
    TCCR1B = (uint8_t)((1u << WGM12) | (1u << CS12) | (1u << CS10));
    OCR1A = 15624u;
    TIMSK1 = (uint8_t)(1u << OCIE1A);
    TCNT1 = 0u;
}

uint8_t Timer1_consume_1s_tick(void)
{
    uint8_t oldSREG = SREG;
    cli(); /* so isr cant stomp s_pending while we read/clear it */
    uint8_t v = s_pending_1s;
    s_pending_1s = 0u;
    SREG = oldSREG;
    return v;
}
