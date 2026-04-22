// --- buzzer header ---
// this module gives simple buzzer control used by TrafficLight violation logic.
#ifndef BUZZER_H
#define BUZZER_H

// Buzzer_init prepares buzzer output low so startup is silent.
void Buzzer_init(void);
// Buzzer_beep_once emits one short alert pulse.
void Buzzer_beep_once(void);

#endif
