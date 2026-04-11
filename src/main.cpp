/*
 * NET3001 final project
 *    traffic light + ultrasonic sensor red light checker
 * group 19
 */
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
    /* gpio first — if you skip this pins float wierd */
    GPIO_init();
    USART0_init_9600();
    LCD_init();
    SevenSeg_init();
    Buzzer_init();
    Ultrasound_init();
    PCINT_buttons_init();
    /*
  * timer1 init after other stuff
     * so we dont get random ticks mid init
 */
    Timer1_init_1Hz_tick();
    TrafficLight_init();
    sei(); /* global interrupts */
}

void loop(void)
{
    /* everything happens in TrafficLight_step */
    TrafficLight_step();
}
