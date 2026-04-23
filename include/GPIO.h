/*
 * GPIO MODULE HEADER
 *
 * Possible question: "Why do this in one function?"
 * Answer: Centralized hardware initialization avoids duplicated setup and
 * inconsistent pin direction/levels across modules.
 */
#ifndef GPIO_H
#define GPIO_H

// Applies DDR and PORT defaults for all mapped peripherals.
void GPIO_init(void);

#endif
