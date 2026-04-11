/* print to serial monitor at 9600 */
#ifndef USART0_H
#define USART0_H

#include <stdint.h>

void USART0_init_9600(void);
void USART0_print(const char *s);
void USART0_print_u16(uint16_t v);

#endif
