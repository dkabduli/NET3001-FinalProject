/*
 * SHIFT REGISTER DISPLAY HEADER - Rewritten contract
 *
 * Note:
 * - This header represents the project's "ShiftReg module" API through the
 *   SevenSeg abstraction.
 *
 * What this header defines:
 * - Public functions to initialize and update the shift-register-driven display.
 *
 * Why this interface matters:
 * - Other modules can render digits without managing serial bit shifting,
 *   latch timing, or segment encoding.
 * - A small API keeps higher-level traffic logic independent from display wiring.
 *
 * Why structured this way:
 * - Include guards ensure safe multi-include behavior.
 * - Encapsulation at the header boundary protects callers from hardware-level
 *   implementation details that may change during future refinements.
 *
 * Possible question: "Where is ShiftReg implemented?"
 * Answer: In SevenSeg.cpp via SER/CLK/RCK helper routines.
 */
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

// SevenSeg_init keeps init symmetry with other modules.
void SevenSeg_init(void);
// SevenSeg_show_digit updates segments for value zero to nine.
void SevenSeg_show_digit(uint8_t d);

#endif
