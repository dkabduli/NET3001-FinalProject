// NET3001 final group 19
// traffic light + ultrasonic + th e red-light check
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
    GPIO_init();
    USART0_init_9600();
    LCD_init();
    SevenSeg_init();
    Buzzer_init();
    Ultrasound_init();
    PCINT_buttons_init();
    Timer1_init_1Hz_tick();
    TrafficLight_init();
    sei(); // interupts on (global)
}

void loop(void)
{
    TrafficLight_step();
}
