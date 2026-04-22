// dist in cm — echo pulse stuff
#include <Arduino.h>    // AVR port register names
#include <util/delay.h> // microsecond delays for trigger and timing loop
#include <stdint.h>     // uint16_t type for microsecond counters
#include "Ultrasonic.h" // ultrasonic public API
#include "PinMap.h"     // trigger and echo pin mappings

// --- ultrasonic module ---
// Ultrasound_init currently has no runtime setup because GPIO_init already
// configured trigger as output and echo as input pullup.
void Ultrasound_init(void)
{
    // no body needed since GPIO_init already sets trigger and echo directions
}

// Ultrasound_read_cm sends a 10us trigger pulse then measures echo high time.
// it returns distance in cm using approx conversion us/58.
// return 0 means timeout or invalid echo pulse.
uint16_t Ultrasound_read_cm(void)
{
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT); // ensure clean low before trigger
    _delay_us(2); // settle line low
    SONIC_TRIG_PORT |= (uint8_t)(1u << SONIC_TRIG_BIT); // start trigger pulse
    _delay_us(10); // hold trigger high for sensor requirement
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT); // end trigger pulse

    uint16_t wait = 0u; // timeout counter while waiting echo to rise
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) == 0u) {
        _delay_us(1); // one microsecond step
        if (++wait > 30000u)
            return 0u; // timeout means no valid echo start
    }
    uint16_t us = 0u; // pulse width counter in microseconds
    while ((SONIC_ECHO_PIN & (1u << SONIC_ECHO_BIT)) != 0u) {
        _delay_us(1); // one microsecond step
        if (++us > 30000u)
            return 0u; // timeout means echo stayed high too long
    }
    return (uint16_t)(us / 58u); // /58 approx from  online
}
