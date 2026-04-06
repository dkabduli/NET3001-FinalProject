/* 1 Hz tick flag from Timer1 compare ISR */
#ifndef TIMER1TICK_H
#define TIMER1TICK_H

#include <stdint.h>

void Timer1_init_1Hz_tick(void);
uint8_t Timer1_consume_1s_tick(void);

#endif
