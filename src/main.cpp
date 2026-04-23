// NET3001 final group 19
// traffic light and ultrasonic an dred-light check
#include <Arduino.h>       // Arduino core glue for AVR build environment
#include <avr/interrupt.h> // gives sei() for global interrupt enable
#include "GPIO.h"          // pin direction and default level setup
#include "USART0.h"        // serial debug output setup
#include "LCD.h"           // lcd driver setup
#include "SevenSeg.h"      // seven segment driver setup
#include "Buzzer.h"        // buzzer driver setup
#include "Ultrasonic.h"    // ultrasonic sensor setup
#include "PCINT_buttons.h" // button interrupt setup
#include "Timer1Tick.h"    // one second timer setup
#include "TrafficLight.h"  // top level traffic control logic

// --- startup wiring ---
// setup initializes every module once, then enables global interrupts.
// it connects low level drivers first, then starts the traffic logic.
void setup(void)
{
    GPIO_init(); // set all DDR and pullup defaults first
    // Defined in: src/GPIO.cpp
    USART0_init_9600(); // prepare serial logging
    // Defined in: src/USART0.cpp
    LCD_init(); // initialize lcd controller and clear screen
    // Defined in: src/LCD.cpp
    SevenSeg_init(); // keep module init sequence consistent
    // Defined in: src/SevenSeg.cpp
    Buzzer_init(); // ensure buzzer starts low
    // Defined in: src/Buzzer.cpp
    Ultrasound_init(); // keep ultrasonic module lifecycle explicit
    // Defined in: src/Ultrasonic.cpp
    PCINT_buttons_init(); // enable pause and reset pin change interrupts
    // Defined in: src/PCINT_buttons.cpp
    Timer1_init_1Hz_tick(); // start one second heartbeat source
    // Defined in: src/Timer1Tick.cpp
    TrafficLight_init(); // initialize state machine and outputs
    // Defined in: src/TrafficLight.cpp
    sei(); // global interrupt enable after all modules are ready
}

// --- runtime loop ---
// loop stays tiny and delegates behavior to the traffic state machine.
void loop(void)
{
    TrafficLight_step(); // run one control iteration each loop cycle
    // Defined in: src/TrafficLight.cpp
}
