/*
 * USART0 MODULE HEADER - Rewritten contract
 *
 * What this header defines:
 * - Public serial API for initializing UART and printing strings/uint16 values.
 * - A narrow, reliable interface for diagnostics and event logging.
 *
 * Why this interface matters:
 * - Application modules can emit useful runtime information without touching
 *   hardware registers or duplicating UART setup logic.
 * - Shared, centralized serial routines keep output format and behavior
 *   consistent across the project.
 *
 * Why structured this way:
 * - Include guards ensure safe repeated inclusion on all supported compilers.
 * - The interface is kept compact to reduce coupling and preserve flexibility
 *   for internal UART implementation changes.
 *
 * Possible question: "Why is only a small API exposed?"
 * Answer: Keeping UART internals private reduces coupling and misuse.
 */
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
