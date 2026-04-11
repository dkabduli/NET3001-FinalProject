/*
 * LCD 4 bit mode
 *    timing from datasheet / lab handout
 */
#include <Arduino.h>
#include <util/delay.h>
#include <stdint.h>
#include "LCD.h"
#include "PinMap.h"

static void lcd_nibble_write(uint8_t nibble, uint8_t rs)
{
    if (rs != 0u)
        LCD_RS_PORT |= (uint8_t)(1u << LCD_RS_BIT);
    else
        LCD_RS_PORT &= (uint8_t) ~(1u << LCD_RS_BIT);

    /* mash bits onto D4-D7 */
    LCD_D4_PORT = (LCD_D4_PORT & (uint8_t) ~(1u << LCD_D4_BIT)) |
                  (uint8_t)(((nibble >> 0) & 1u) << LCD_D4_BIT);
    LCD_D5_PORT = (LCD_D5_PORT & (uint8_t) ~(1u << LCD_D5_BIT)) |
                  (uint8_t)(((nibble >> 1) & 1u) << LCD_D5_BIT);
    LCD_D6_PORT = (LCD_D6_PORT & (uint8_t) ~(1u << LCD_D6_BIT)) |
                  (uint8_t)(((nibble >> 2) & 1u) << LCD_D6_BIT);
    LCD_D7_PORT = (LCD_D7_PORT & (uint8_t) ~(1u << LCD_D7_BIT)) |
                  (uint8_t)(((nibble >> 3) & 1u) << LCD_D7_BIT);
    LCD_EN_PORT |= (uint8_t)(1u << LCD_EN_BIT);
    _delay_us(1);
    LCD_EN_PORT &= (uint8_t) ~(1u << LCD_EN_BIT);
    _delay_us(100);
}

static void lcd_byte_write(uint8_t value, uint8_t rs)
{
    lcd_nibble_write((uint8_t)(value >> 4), rs);
    lcd_nibble_write((uint8_t)(value & 0x0Fu), rs);
    _delay_us(100);
}

void LCD_init(void)
{
    _delay_ms(50);
    lcd_nibble_write(0x03u, 0u);
    _delay_ms(5);
    lcd_nibble_write(0x03u, 0u);
    _delay_us(200);
    lcd_nibble_write(0x03u, 0u);
    lcd_nibble_write(0x02u, 0u);
    lcd_byte_write(0x28u, 0u); /* 2 line mode */
    lcd_byte_write(0x0Cu, 0u);
    lcd_byte_write(0x06u, 0u);
    LCD_clear();
}

void LCD_clear(void)
{
    lcd_byte_write(0x01u, 0u);
    _delay_ms(2);
}

static void lcd_putc(char c)
{
    lcd_byte_write((uint8_t)c, 1u);
}

static void lcd_goto(uint8_t row, uint8_t col)
{
    static const uint8_t row_off[2] = {0x80u, 0xC0u};
    lcd_byte_write((uint8_t)(row_off[row] + col), 0u);
}

void LCD_line1(const char *text)
{
    lcd_goto(0, 0);
    uint8_t n = 0u;
    while (n < 16u && text[n] != '\0')
        lcd_putc(text[n++]);
    while (n < 16u) {
        lcd_putc(' ');
        n++;
    } /* pad or junk chars stay visable */
}

void LCD_line2(const char *text)
{
    lcd_goto(1, 0);
    uint8_t n = 0u;
    while (n < 16u && text[n] != '\0')
        lcd_putc(text[n++]);
    while (n < 16u) {
        lcd_putc(' ');
        n++;
    }
}
