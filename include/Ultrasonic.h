#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

void Ultrasound_init(void);
uint16_t Ultrasound_read_cm(void);

#endif
