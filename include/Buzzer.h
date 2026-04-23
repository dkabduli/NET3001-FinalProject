/*
 * BUZZER MODULE HEADER
 *
 * Possible question: "What is public here?"
 * Answer: These are the functions other files can call.
 */
#ifndef BUZZER_H
#define BUZZER_H

// Set buzzer to a safe startup state.
void Buzzer_init(void);
// Play one short beep.
void Buzzer_beep_once(void);

#endif
