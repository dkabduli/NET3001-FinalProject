/*
 * our module is a piezo — tone() makes it actually loud. just digitalWrite high was
 * super quiet. uses timer2 internally i think, timer1 is still our 1hz tick
 */
#include <Arduino.h>
#include "Buzzer.h"
#include "PinMap.h"

/* arduino pin number for PD3 — has to match pinmap or it wont compile right */
static const uint8_t kBuzArduinoPin = 3u;

void Buzzer_init(void)
{
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT);
}

void Buzzer_beep_once(void)
{
    /* double beep so you actually notice it */
    tone(kBuzArduinoPin, 2500);
    delay(200);
    noTone(kBuzArduinoPin);
    delay(45);
    tone(kBuzArduinoPin, 2500);
    delay(200);
    noTone(kBuzArduinoPin);
}
