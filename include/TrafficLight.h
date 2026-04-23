/*
 * TRAFFIC LIGHT MODULE HEADER
 *
 * Possible question: "Why use #ifndef instead of #pragma once?"
 * Answer: Include guards are fully portable across embedded toolchains.
 */
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

// Public API: initialize state machine and all display state assumptions.
void TrafficLight_init(void);
// Public API: call repeatedly from Arduino loop() for non-blocking operation.
void TrafficLight_step(void);

#endif
