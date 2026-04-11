/*
 * Ultrasonic sensor distance
 *   blocking loops — if echo takes forever we bail with 0
 */
#include <Arduino.h>
#include <util/delay.h>
#include <stdint.h>
#include "Ultrasonic.h"
#include "PinMap.h"

void Ultrasound_init(void)
{
}

uint16_t Ultrasound_read_cm(void)
{
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT);
    _delay_us(2);
    SONIC_TRIG_PORT |= (uint8_t)(1u << SONIC_TRIG_BIT);
    _delay_us(10);
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT);

    uint16_t wait = 0u;
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) == 0u) {
        _delay_us(1);
        if (++wait > 30000u)
            return 0u; /* nothing came back */
    }
    uint16_t us = 0u;
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) != 0u) {
        _delay_us(1);
        if (++us > 30000u)
            return 0u;
    }
    /*
  * /58 rule from internet
     * not perfect but ok for this assingment
 */
    return (uint16_t)(us / 58u);
}
