/* serial 9600 — print strings and u16 for violation distance */
#ifndef USART0_H
#define USART0_H

#include <stdint.h>

void USART0_init_9600(void);
void USART0_print(const char *s);
void USART0_print_u16(uint16_t v);

#endif
