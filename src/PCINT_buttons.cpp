#include <Arduino.h>       // gives AVR register and core definitions
#include <avr/interrupt.h> // gives ISR() macro and cli() declaration
#include <util/delay.h>    // gives _delay_ms() used for debounce timing
#include <stdint.h>        // gives uint8_t fixed width integer type
#include "PCINT_buttons.h" // this module public declarations
#include "PinMap.h"        // pause and reset pin mapping macros

// --- edge flags set by interrupts ---
static volatile uint8_t s_pause_edge; // set to 1 when pause pin change interrupt fires
static volatile uint8_t s_reset_edge; // set to 1 when reset pin change interrupt fires

// PCINT0 ISR marks that pause pin changed.
// it only sets a flag; debounce happens later in main context.
ISR(PCINT0_vect)
{
    s_pause_edge = 1u; // mark pause edge pending for main loop to process
}

// PCINT1 ISR marks that reset pin changed.
// same design: keep ISR tiny and do filtering outside ISR.
ISR(PCINT1_vect)
{
    s_reset_edge = 1u; // mark reset edge pending for main loop to process
}

// --- interrupt mask setup ---
// PCINT_buttons_init enables pin change groups and selects pause and reset pins.
void PCINT_buttons_init(void)
{
    PCICR |= (uint8_t)((1u << PCIE0) | (1u << PCIE1)); // enable pin change interrupt groups 0 and 1
    PCMSK0 |= (uint8_t)(1u << PCINT2);                 // unmask PB2 pin change source for pause button
    PCMSK1 |= (uint8_t)(1u << PCINT8);                 // unmask PC0 pin change source for reset button
}

// --- atomic flag readers ---
// take_pause safely reads then clears pause edge flag.
static uint8_t take_pause(void)
{
    uint8_t oldSREG = SREG; // save global interrupt enable state
    cli();                  // disable interrupts for atomic flag access
    uint8_t v = s_pause_edge; // copy current pause edge flag
    s_pause_edge = 0u;        // clear flag so one edge is consumed once
    SREG = oldSREG;           // restore previous interrupt state
    return v;                 // return 1 if edge was pending, else 0
}

// take_reset safely reads then clears reset edge flag.
static uint8_t take_reset(void)
{
    uint8_t oldSREG = SREG; // save global interrupt enable state
    cli();                  // disable interrupts for atomic flag access
    uint8_t v = s_reset_edge; // copy current reset edge flag
    s_reset_edge = 0u;        // clear flag so one edge is consumed once
    SREG = oldSREG;           // restore previous interrupt state
    return v;                 // return 1 if edge was pending, else 0
}

// --- pin level samplers ---
// stable_low_pause returns 1 when pause button is physically pressed.
static uint8_t stable_low_pause(void)
{
    return (BTN_PAUSE_PIN & (1u << BTN_PAUSE_BIT)) == 0u; // active low means pressed when read bit is 0
}

// stable_low_reset returns 1 when reset button is physically pressed.
static uint8_t stable_low_reset(void)
{
    return (BTN_RESET_PIN & (1u << BTN_RESET_BIT)) == 0u; // active low means pressed when read bit is 0
}

// --- debounced click API ---
// PCINT_consume_pause_click debounces a pause edge and waits release.
// returns 1 once per valid click, else 0.
uint8_t PCINT_consume_pause_click(void)
{
    if (take_pause() == 0u) // exit if no edge was captured
        return 0u;          // no click event to consume
    _delay_ms(25);          // first debounce wait after interrupt edge
    if (stable_low_pause() == 0u) // if line bounced back high this was noise
        return 0u;               // reject false click
    while (stable_low_pause() != 0u) {
        // wait here until user releases button
    }
    _delay_ms(25); // release debounce wait to avoid double count
    return 1u;     // report one valid debounced click
}

// PCINT_consume_reset_click debounces reset edge and waits release.
// returns 1 once per valid click, else 0.
uint8_t PCINT_consume_reset_click(void)
{
    if (take_reset() == 0u) // exit if no edge was captured
        return 0u;          // no click event to consume
    _delay_ms(25);          // first debounce wait after interrupt edge
    if (stable_low_reset() == 0u) // if line bounced back high this was noise
        return 0u;               // reject false click
    while (stable_low_reset() != 0u) {
        // wait here until user releases button
    }
    _delay_ms(25); // release debounce wait to avoid double count
    return 1u;     // report one valid debounced click
}
