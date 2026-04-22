// --- gpio header ---
// GPIO_init configures all pin directions and safe startup levels.
// other modules assume setup() calls this before they run.
#ifndef GPIO_H
#define GPIO_H

// GPIO_init applies DDR and PORT defaults for leds buttons lcd buzzer and sensors.
void GPIO_init(void);

#endif
