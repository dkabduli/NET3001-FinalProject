/* HC-SR04 — blocking pulse measure, not ideal but ok for this loop */
#include <Arduino.h>
#include <util/delay.h>
#include <stdint.h>
#include "Ultrasonic.h"
#include "PinMap.h"

void Ultrasound_init(void)
{
    /* gpio already did trig/echo */
}

uint16_t Ultrasound_read_cm(void)
{
    /* 10us trigger */
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT);
    _delay_us(2);
    SONIC_TRIG_PORT |= (uint8_t)(1u << SONIC_TRIG_BIT);
    _delay_us(10);
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT);

    uint16_t wait = 0u;
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) == 0u) {
        _delay_us(1);
        if (++wait > 30000u)
            return 0u; /* no echo, return 0 so caller ignores */
    }
    uint16_t us = 0u;
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) != 0u) {
        _delay_us(1);
        if (++us > 30000u)
            return 0u;
    }
    /* /58 thing from datasheet / forums, works ok becuase were not doing lab precision */
    return (uint16_t)(us / 58u);
}
