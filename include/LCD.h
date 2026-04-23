/*
 * LCD MODULE HEADER - Rewritten contract
 *
 * What this header defines:
 * - Minimal public API for LCD control: init, clear, line1, line2.
 * - A clean boundary between application logic and low-level LCD signaling.
 *
 * Why this interface matters:
 * - Callers can update display content without depending on command bytes,
 *   bus timings, or pin-level sequencing details.
 * - Keeping only essential entry points reduces misuse and keeps behavior
 *   consistent across the project.
 *
 * Why structured this way:
 * - Include guards keep compatibility with conservative AVR toolchains.
 * - The header intentionally exposes only stable operations and hides helper
 *   primitives so internals can evolve without breaking other modules.
 *
 * Possible question: "Why #ifndef instead of #pragma once?"
 * Answer: #ifndef include guards are portable across older embedded toolchains.
 */
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
