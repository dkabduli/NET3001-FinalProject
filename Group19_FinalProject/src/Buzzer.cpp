/* Active buzzer — just drive the pin high for a bit */
#include <Arduino.h>
#include <util/delay.h>
#include "Buzzer.h"
#include "PinMap.h"

void Buzzer_init(void)
{
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT);
}

void Buzzer_beep_once(void)
{
    BUZ_PORT |= (uint8_t)(1u << BUZ_BIT);
    _delay_ms(60); // length is arbitrary, sounds ok on ours
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT);
}
