// all th e ddr port defs in one place if u mess up wiring fix here
// --- board pin map header ---
// each macro maps one logical signal to avr DDR PORT PIN and bit number.
// modules include this so hardware wiring stays centralized in one file.
#ifndef PINMAP_H
#define PINMAP_H

#include <stdint.h>

#define LED_GRN_DDR DDRC
#define LED_GRN_PORT PORTC
#define LED_GRN_BIT 2u

#define LED_AMB_DDR DDRC
#define LED_AMB_PORT PORTC
#define LED_AMB_BIT 3u

#define LED_RED_DDR DDRC
#define LED_RED_PORT PORTC
#define LED_RED_BIT 4u

#define BTN_PAUSE_DDR DDRB
#define BTN_PAUSE_PIN PINB
#define BTN_PAUSE_PORT PORTB
#define BTN_PAUSE_BIT 2u

#define BTN_RESET_DDR DDRC
#define BTN_RESET_PIN PINC
#define BTN_RESET_PORT PORTC
#define BTN_RESET_BIT 0u

#define BUZ_DDR DDRD
#define BUZ_PORT PORTD
#define BUZ_BIT 3u

#define SONIC_TRIG_DDR DDRC
#define SONIC_TRIG_PORT PORTC
#define SONIC_TRIG_BIT 5u

#define SONIC_ECHO_DDR DDRD
#define SONIC_ECHO_PIN PIND
#define SONIC_ECHO_PORT PORTD
#define SONIC_ECHO_BIT 2u

#define SR_SER_DDR DDRB
#define SR_SER_PORT PORTB
#define SR_SER_BIT 3u

#define SR_CLK_DDR DDRB
#define SR_CLK_PORT PORTB
#define SR_CLK_BIT 4u

#define SR_RCK_DDR DDRB
#define SR_RCK_PORT PORTB
#define SR_RCK_BIT 5u

#define LCD_RS_DDR DDRB
#define LCD_RS_PORT PORTB
#define LCD_RS_BIT 0u

#define LCD_EN_DDR DDRB
#define LCD_EN_PORT PORTB
#define LCD_EN_BIT 1u

#define LCD_D4_DDR DDRD
#define LCD_D4_PORT PORTD
#define LCD_D4_BIT 4u

#define LCD_D5_DDR DDRD
#define LCD_D5_PORT PORTD
#define LCD_D5_BIT 5u

#define LCD_D6_DDR DDRD
#define LCD_D6_PORT PORTD
#define LCD_D6_BIT 6u

#define LCD_D7_DDR DDRD
#define LCD_D7_PORT PORTD
#define LCD_D7_BIT 7u

#endif
