/* one digit countdown on 7-segment */
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

void SevenSeg_init(void);
void SevenSeg_show_digit(uint8_t d);

#endif
