/*
 * TIMER1 TICK MODULE HEADER
 *
 * Possible question: "Why have a 1 Hz tick module?"
 * Answer: It decouples timing from business logic. TrafficLight consumes ticks
 * instead of manually counting delays in blocking loops.
 */
#ifndef TIMER1TICK_H
#define TIMER1TICK_H

#include <stdint.h>

// Configures Timer1 compare interrupt to produce a one-second event flag.
void Timer1_init_1Hz_tick(void);
// Returns pending 1-second flag (0/1) and clears it after read.
uint8_t Timer1_consume_1s_tick(void);

#endif
