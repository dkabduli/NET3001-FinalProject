/* pause / reset buttons */
#ifndef PCINT_BUTTONS_H
#define PCINT_BUTTONS_H

#include <stdint.h>

void PCINT_buttons_init(void);
uint8_t PCINT_consume_pause_click(void);
uint8_t PCINT_consume_reset_click(void);

#endif
