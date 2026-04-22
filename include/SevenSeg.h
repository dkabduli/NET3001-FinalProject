// ifndef guard keeps header safe if included more than once
// --- seven segment header ---
// this module drives one digit through external shift register pins.
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

// SevenSeg_init keeps init symmetry with other modules.
void SevenSeg_init(void);
// SevenSeg_show_digit updates segments for value zero to nine.
void SevenSeg_show_digit(uint8_t d);

#endif
