// paralell 16x2 lcd
// using ifndef guard instead of pragma once so this stays portable on older toolchains
// --- lcd header ---
// lcd module writes text using hd44780 style commands in 4 bit bus mode.
#ifndef LCD_H
#define LCD_H

// LCD_init runs lcd startup sequence and display defaults.
void LCD_init(void);
// LCD_clear clears display and homes cursor.
void LCD_clear(void);
// LCD_line1 writes row one and pads spaces to full width.
void LCD_line1(const char *text);
// LCD_line2 writes row two and pads spaces to full width.
void LCD_line2(const char *text);

#endif
