/*
 * BUZZER MODULE HEADER
 *
 * Possible question: "What is public here?"
 * Answer: These declarations are the public functions callable by other files.
 */
#ifndef BUZZER_H
#define BUZZER_H

// Initializes buzzer pin state (safe startup, no accidental beep).
void Buzzer_init(void);
// Emits one short alert pulse used by violation detection.
void Buzzer_beep_once(void);

#endif
