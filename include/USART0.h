// usart 9600 8n1
// ifndef guard avoids double include no matter compiler settings
// --- usart header ---
// this module gives basic serial printing for debug and violation logging.
#ifndef USART0_H
#define USART0_H

#include <stdint.h>

// USART0_init_9600 configures uart registers for 9600 baud.
void USART0_init_9600(void);
// USART0_print sends null terminated text string.
void USART0_print(const char *s);
// USART0_print_u16 sends unsigned 16 bit integer as decimal text.
void USART0_print_u16(uint16_t v);

#endif
