/* 16x2 in 4-bit mode */
#ifndef LCD_H
#define LCD_H

void LCD_init(void);
void LCD_clear(void);
void LCD_line1(const char *text);
void LCD_line2(const char *text);

#endif
