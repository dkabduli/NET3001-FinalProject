/* Serial.print under the hood would work too — this is bare registers for the course */
#include <Arduino.h>
#include <stdint.h>
#include "USART0.h"

void USART0_init_9600(void)
{
    UBRR0H = 0u;
    UBRR0L = 103u;
    UCSR0A = 0u;
    UCSR0B = (uint8_t)((1u << TXEN0) | (1u << RXEN0));
    UCSR0C = (uint8_t)((1u << UCSZ01) | (1u << UCSZ00));
}

static void USART0_tx_byte(uint8_t b)
{
    while ((UCSR0A & (1u << UDRE0)) == 0u) {
    } // spin until TX buffer free
    UDR0 = b;
}

void USART0_print(const char *s)
{
    if (s == 0)
        return;
    while (*s != '\0')
        USART0_tx_byte((uint8_t)*s++);
}

static void print_digits(uint16_t v)
{
    if (v == 0u) {
        USART0_tx_byte((uint8_t)'0');
        return;
    }
    char tmp[6]; // stack buffer, print reversed
    uint8_t i = 0u;
    while (v > 0u && i < sizeof(tmp)) {
        tmp[i++] = (char)('0' + (v % 10u));
        v /= 10u;
    }
    while (i > 0u)
        USART0_tx_byte((uint8_t)tmp[--i]);
}

void USART0_print_u16(uint16_t v)
{
    print_digits(v);
}
