// pause and reset debounce in c file
// --- button interrupt header ---
// this module turns noisy pin change edges into clean button clicks.
#ifndef PCINT_BUTTONS_H
#define PCINT_BUTTONS_H

#include <stdint.h>

// PCINT_buttons_init enables pin change interrupts for pause and reset pins.
void PCINT_buttons_init(void);
// PCINT_consume_pause_click returns 1 once per debounced pause click.
uint8_t PCINT_consume_pause_click(void);
// PCINT_consume_reset_click returns 1 once per debounced reset click.
uint8_t PCINT_consume_reset_click(void);

#endif
