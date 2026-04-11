/* NET3001 final — traffic light + ultrasonic thing, group 19 */
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
    /* gpio first so pins arent floating */
    GPIO_init();
    USART0_init_9600();
    LCD_init();
    SevenSeg_init();
    Buzzer_init();
    Ultrasound_init();
    PCINT_buttons_init();
    /* timer after other stuff so we dont miss ticks during init */
    Timer1_init_1Hz_tick();
    TrafficLight_init();
    sei(); /* ints on last */
}

void loop(void)
{
    /* all the real logic is in TrafficLight_step, loop is just that */
    TrafficLight_step();
}
