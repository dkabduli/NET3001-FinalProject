#include <Arduino.h>
#include <stdint.h>
#include "GPIO.h"
#include "PinMap.h"

// output low — LEDs, shift reg lines, buzzer, trig, LCD control/data
static void out1(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit)
{
    *ddr |= (uint8_t)(1u << bit);
    *port &= (uint8_t) ~(1u << bit);
}

// buttons go to gnd when pressed so internal pullup = idle high
static void in_pullup(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit)
{
    *ddr &= (uint8_t) ~(1u << bit);
    *port |= (uint8_t)(1u << bit);
}

void GPIO_init(void)
{
    // kinda tedious but beats wiring mistakes later
    out1(&LED_GRN_DDR, &LED_GRN_PORT, LED_GRN_BIT);
    out1(&LED_AMB_DDR, &LED_AMB_PORT, LED_AMB_BIT);
    out1(&LED_RED_DDR, &LED_RED_PORT, LED_RED_BIT);

    out1(&BUZ_DDR, &BUZ_PORT, BUZ_BIT);
    BUZ_PORT &= (uint8_t) ~(1u << BUZ_BIT);
    out1(&SONIC_TRIG_DDR, &SONIC_TRIG_PORT, SONIC_TRIG_BIT);
    SONIC_TRIG_PORT &= (uint8_t) ~(1u << SONIC_TRIG_BIT);
    in_pullup(&SONIC_ECHO_DDR, &SONIC_ECHO_PORT, SONIC_ECHO_BIT);
    out1(&SR_SER_DDR, &SR_SER_PORT, SR_SER_BIT);
    out1(&SR_CLK_DDR, &SR_CLK_PORT, SR_CLK_BIT);
    out1(&SR_RCK_DDR, &SR_RCK_PORT, SR_RCK_BIT);
    SR_SER_PORT &= (uint8_t) ~(1u << SR_SER_BIT);
    SR_CLK_PORT &= (uint8_t) ~(1u << SR_CLK_BIT);
    SR_RCK_PORT &= (uint8_t) ~(1u << SR_RCK_BIT);
    in_pullup(&BTN_PAUSE_DDR, &BTN_PAUSE_PORT, BTN_PAUSE_BIT);
    in_pullup(&BTN_RESET_DDR, &BTN_RESET_PORT, BTN_RESET_BIT);
    out1(&LCD_RS_DDR, &LCD_RS_PORT, LCD_RS_BIT);
    out1(&LCD_EN_DDR, &LCD_EN_PORT, LCD_EN_BIT);
    out1(&LCD_D4_DDR, &LCD_D4_PORT, LCD_D4_BIT);
    out1(&LCD_D5_DDR, &LCD_D5_PORT, LCD_D5_BIT);
    out1(&LCD_D6_DDR, &LCD_D6_PORT, LCD_D6_BIT);
    out1(&LCD_D7_DDR, &LCD_D7_PORT, LCD_D7_BIT);
}
