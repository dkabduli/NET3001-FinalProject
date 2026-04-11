#include <Arduino.h>
#include <util/delay.h>
#include <stdint.h>
#include "SevenSeg.h"
#include "PinMap.h"

static void pulse_clk(void)
{
    SR_CLK_PORT |= (uint8_t)(1u << SR_CLK_BIT);
    _delay_us(1);
    SR_CLK_PORT &= (uint8_t) ~(1u << SR_CLK_BIT);
}

static void latch(void)
{
    SR_RCK_PORT |= (uint8_t)(1u << SR_RCK_BIT);
    _delay_us(1);
    SR_RCK_PORT &= (uint8_t) ~(1u << SR_RCK_BIT);
}

static void sr_send(uint8_t b)
{
    for (uint8_t i = 0u; i < 8u; i++) {
        if ((b & 0x80u) != 0u)
            SR_SER_PORT |= (uint8_t)(1u << SR_SER_BIT);
        else
            SR_SER_PORT &= (uint8_t) ~(1u << SR_SER_BIT);
        b = (uint8_t)(b << 1);
        pulse_clk();
    }
}

void SevenSeg_init(void)
{
}

void SevenSeg_show_digit(uint8_t d)
{
    static const uint8_t map[10] = {0x3Fu, 0x06u, 0x5Bu, 0x4Fu, 0x66u,
                                    0x6Du, 0x7Du, 0x07u, 0x7Fu, 0x6Fu};
    if (d > 9u)
        d = 9u;
    sr_send(map[d]);
    latch();
}
