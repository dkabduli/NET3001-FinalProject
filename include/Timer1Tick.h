// --- timer tick header ---
// timer1 module provides one second heartbeat for traffic countdown logic.
#ifndef TIMER1TICK_H
#define TIMER1TICK_H

#include <stdint.h>

// Timer1_init_1Hz_tick configures timer1 compare interrupt at one hertz.
void Timer1_init_1Hz_tick(void);
// Timer1_consume_1s_tick returns pending tick flag then clears it.
uint8_t Timer1_consume_1s_tick(void);

#endif
