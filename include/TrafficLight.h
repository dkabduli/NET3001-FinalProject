// ifndef guard keeps this declaration file one copy per compile unit
// --- traffic state machine header ---
// this module coordinates leds lcd sensor buttons timer and buzzer behavior.
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

// TrafficLight_init sets startup phase and output state.
void TrafficLight_init(void);
// TrafficLight_step runs one loop slice of control logic.
void TrafficLight_step(void);

#endif
