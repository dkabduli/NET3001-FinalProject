/* main state machine — lights, 7seg countdown, red light + HC-SR04 "camera" */
#include <Arduino.h>
#include <stdint.h>
#include "TrafficLight.h"
#include "PinMap.h"
#include "LCD.h"
#include "SevenSeg.h"
#include "Ultrasonic.h"
#include "Buzzer.h"
#include "USART0.h"
#include "PCINT_buttons.h"
#include "Timer1Tick.h"

typedef enum { PH_GREEN = 0, PH_AMBER, PH_RED } phase_t;

static phase_t s_phase;
static uint8_t s_sec_left;     /* seconds left in this color phase */
static uint8_t s_running;      /* 0 = paused */
static uint8_t s_violation_lcd_ticks; /* how many 1s ticks to keep VIOLATION on lcd before normal text */

/* far/near in cm — tuned on real hardware, sim wasnt the same */
static const uint16_t ZONE_FAR_CM = 45u;
static const uint16_t ZONE_NEAR_CM = 18u;

static uint16_t s_prev_cm; /* last reading for edge detect */
static uint8_t s_armed;    /* after a violation we dont retrigger till car is far again */

static void leds_only_green(void)
{
    LED_GRN_PORT |= (uint8_t)(1u << LED_GRN_BIT);
    LED_AMB_PORT &= (uint8_t) ~(1u << LED_AMB_BIT);
    LED_RED_PORT &= (uint8_t) ~(1u << LED_RED_BIT);
}

static void leds_only_amber(void)
{
    LED_GRN_PORT &= (uint8_t) ~(1u << LED_GRN_BIT);
    LED_AMB_PORT |= (uint8_t)(1u << LED_AMB_BIT);
    LED_RED_PORT &= (uint8_t) ~(1u << LED_RED_BIT);
}

static void leds_only_red(void)
{
    LED_GRN_PORT &= (uint8_t) ~(1u << LED_GRN_BIT);
    LED_AMB_PORT &= (uint8_t) ~(1u << LED_AMB_BIT);
    LED_RED_PORT |= (uint8_t)(1u << LED_RED_BIT);
}

/* normal driving messages, not the violation screen */
static void lcd_normal(void)
{
    if (s_phase == PH_GREEN) {
        LCD_line1("LIGHT: GREEN");
        LCD_line2("SAFE TO GO ");
    } else if (s_phase == PH_AMBER) {
        LCD_line1("LIGHT: AMBER");
        LCD_line2("PREPARE STOP ");
    } else {
        LCD_line1("LIGHT: RED ");
        LCD_line2("STOP ");
    }
}

void TrafficLight_init(void)
{
    s_phase = PH_GREEN;
    s_sec_left = 10u;
    s_running = 1u;
    s_violation_lcd_ticks = 0u;
    s_prev_cm = 999u;
    s_armed = 1u;
    leds_only_green();
    SevenSeg_show_digit(s_sec_left);
    lcd_normal();
}

static void next_phase(void)
{
    /* green -> amber 5s -> red 10s -> green... */
    if (s_phase == PH_GREEN) {
        s_phase = PH_AMBER;
        s_sec_left = 5u;
        leds_only_amber();
    } else if (s_phase == PH_AMBER) {
        s_phase = PH_RED;
        s_sec_left = 10u;
        leds_only_red();
        s_prev_cm = 999u;
        s_armed = 1u;
    } else {
        s_phase = PH_GREEN;
        s_sec_left = 10u;
        leds_only_green();
    }
    SevenSeg_show_digit(s_sec_left);
    lcd_normal();
}

static void tick_one_second(void)
{
    if (s_running == 0u)
        return; /* pause button stops the countdown */
    if (s_sec_left > 1u) {
        s_sec_left--;
        SevenSeg_show_digit(s_sec_left);
        return;
    }
    next_phase();
}

static void handle_violation(uint16_t cm)
{
    Buzzer_beep_once();
    LCD_line1("VIOLATION! ");
    LCD_line2("RED LIGHT RUN");
    s_violation_lcd_ticks = 2u; /* 2 seconds-ish to read it before lcd goes back */
    USART0_print("VIOLATION dist=");
    USART0_print_u16(cm);
    USART0_print(" cm\r\n");
}

static void poll_red_camera(void)
{
    if (s_phase != PH_RED || s_running == 0u)
        return;

    uint16_t cm = Ultrasound_read_cm();
    if (cm == 0u)
        return; /* timeout / glitch, skip */

    /* far then near while red = ran the light (wich is what we count) */
    if (s_armed != 0u && s_prev_cm >= ZONE_FAR_CM && cm <= ZONE_NEAR_CM) {
        handle_violation(cm);
        s_armed = 0u;
    }
    if (cm >= ZONE_FAR_CM)
        s_armed = 1u;
    s_prev_cm = cm;
}

void TrafficLight_step(void)
{
    if (PCINT_consume_pause_click() != 0u)
        s_running = (uint8_t)(1u - s_running);

    if (PCINT_consume_reset_click() != 0u) {
        /* reset goes straight to green full 10s */
        s_phase = PH_GREEN;
        s_sec_left = 10u;
        s_running = 1u;
        leds_only_green();
        SevenSeg_show_digit(s_sec_left);
        lcd_normal();
        s_prev_cm = 999u;
        s_armed = 1u;
    }
    if (Timer1_consume_1s_tick() != 0u) {
        if (s_violation_lcd_ticks > 0u) {
            s_violation_lcd_ticks--;
            if (s_violation_lcd_ticks == 0u)
                lcd_normal();
        } else
            tick_one_second();
    }
    poll_red_camera();
}
