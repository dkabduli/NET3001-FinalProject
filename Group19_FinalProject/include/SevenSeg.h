/* Single digit 0-9 on 7-seg via 74HC595 */
#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

void SevenSeg_init(void);
void SevenSeg_show_digit(uint8_t d);

#endif
