/* Pin-change ISRs for the two buttons — debounce lives in "consume" fns */
#include <Arduino.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "PCINT_buttons.h"
#include "PinMap.h"

static volatile uint8_t s_pause_edge;
static volatile uint8_t s_reset_edge;

ISR(PCINT0_vect)
{
    s_pause_edge = 1u;
}

ISR(PCINT1_vect)
{
    s_reset_edge = 1u;
}

void PCINT_buttons_init(void)
{
    PCICR |= (uint8_t)((1u << PCIE0) | (1u << PCIE1));
    PCMSK0 |= (uint8_t)(1u << PCINT2); // pause on PB2
    PCMSK1 |= (uint8_t)(1u << PCINT8); // reset on PC0 (A0)
}

static uint8_t take_pause(void)
{
    uint8_t oldSREG = SREG;
    cli();
    uint8_t v = s_pause_edge;
    s_pause_edge = 0u;
    SREG = oldSREG;
    return v;
}

static uint8_t take_reset(void)
{
    uint8_t oldSREG = SREG;
    cli();
    uint8_t v = s_reset_edge;
    s_reset_edge = 0u;
    SREG = oldSREG;
    return v;
}

static uint8_t stable_low_pause(void)
{
    return (BTN_PAUSE_PIN & (1u << BTN_PAUSE_BIT)) == 0u;
}

static uint8_t stable_low_reset(void)
{
    return (BTN_RESET_PIN & (1u << BTN_RESET_BIT)) == 0u;
}

uint8_t PCINT_consume_pause_click(void)
{
    if (take_pause() == 0u)
        return 0u;
    _delay_ms(25); // cheap debounce — works ok on our switches
    if (stable_low_pause() == 0u)
        return 0u;
    while (stable_low_pause() != 0u) {
    } // wait for release
    _delay_ms(25);
    return 1u;
}

uint8_t PCINT_consume_reset_click(void)
{
    if (take_reset() == 0u)
        return 0u;
    _delay_ms(25);
    if (stable_low_reset() == 0u)
        return 0u;
    while (stable_low_reset() != 0u) {
    }
    _delay_ms(25);
    return 1u;
}
