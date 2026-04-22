// --- ultrasonic header ---
// ultrasonic module reads distance and is used by red light violation detection.
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

// Ultrasound_init is module setup hook, gpio already handles pin directions.
void Ultrasound_init(void);
// Ultrasound_read_cm returns measured distance in centimeters.
// value zero means timeout or invalid echo.
uint16_t Ultrasound_read_cm(void);

#endif
