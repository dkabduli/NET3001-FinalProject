#include <Arduino.h>    // AVR register access
#include <util/delay.h> // short blocking delay for beep duration
#include "Buzzer.h"     // buzzer public API
#include "PinMap.h"     // buzzer pin mapping macros

// --- buzzer control ---
// Buzzer_init guarantees buzzer output starts low so power on is silent.
void Buzzer_init(void)
{
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT); // drive buzzer output low
}

// Buzzer_beep_once gives one short pulse used by violation alerts.
// TrafficLight calls this in handle_violation().
void Buzzer_beep_once(void)
{
    BUZ_PORT |= (uint8_t)(1u << BUZ_BIT); // buzzer on
    _delay_ms(40); // keep beep audible but short
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT); // buzzer off
}
