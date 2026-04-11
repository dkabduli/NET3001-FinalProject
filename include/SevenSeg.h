/* one digit 0-9 on 7seg through 595 shift reg */
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

void SevenSeg_init(void);
void SevenSeg_show_digit(uint8_t d);

#endif
