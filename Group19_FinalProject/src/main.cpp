/* Group 19 — Abdul did the bench setup + serial checks, Isaac did the code side */
#include <Arduino.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "USART0.h"
#include "LCD.h"
#include "SevenSeg.h"
#include "Buzzer.h"
#include "Ultrasonic.h"
#include "PCINT_buttons.h"
#include "Timer1Tick.h"
#include "TrafficLight.h"

void setup(void)
{
    // init order kinda matters — GPIO first then peripherals
    GPIO_init();
    USART0_init_9600();
    LCD_init();
    SevenSeg_init();
    Buzzer_init();
    Ultrasound_init();
    PCINT_buttons_init();
    Timer1_init_1Hz_tick();
    TrafficLight_init();
    sei(); // global ints on after everything's ready
}

void loop(void)
{
    // whole app is basically one state machine tick
    TrafficLight_step();
}
