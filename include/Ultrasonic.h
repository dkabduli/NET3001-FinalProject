/*
 * ULTRASONIC MODULE HEADER
 *
 * Possible question: "What is uint16_t here?"
 * Answer: It is an unsigned 16-bit integer type from <stdint.h>, used because
 * distance values can exceed 255 and fixed-width types are safer in embedded.
 */
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

// Setup hook for module symmetry; GPIO module already sets pin directions.
void Ultrasound_init(void);
// Returns measured distance in centimeters; 0 means timeout/invalid echo.
uint16_t Ultrasound_read_cm(void);

#endif
