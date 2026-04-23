/*
 * GPIO MODULE HEADER
 *
 * Possible question: "Why do this in one function?"
 * Answer: One setup place keeps pins consistent in all modules.
 */
#ifndef GPIO_H
#define GPIO_H

// Set pin directions and default pin levels.
void GPIO_init(void);

#endif
