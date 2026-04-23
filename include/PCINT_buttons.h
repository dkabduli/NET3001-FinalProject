/*
 * BUTTON PCINT MODULE HEADER
 *
 * Possible question: "Why return uint8_t instead of bool?"
 * Answer: uint8_t is explicit 8-bit type commonly used in AVR code and maps
 * cleanly to register-sized flags.
 */
#ifndef PCINT_BUTTONS_H
#define PCINT_BUTTONS_H

#include <stdint.h>

// Enables pin-change interrupts and debounce state for pause/reset inputs.
void PCINT_buttons_init(void);
// Returns 1 once for each debounced pause click, then clears that event.
uint8_t PCINT_consume_pause_click(void);
// Returns 1 once for each debounced reset click, then clears that event.
uint8_t PCINT_consume_reset_click(void);

#endif
