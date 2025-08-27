#ifndef INC_WATCHDOG_H
#define INC_WATCHDOG_H

#include <stdint.h>

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t REASON;
	volatile uint32_t SCRATCH[8];
	volatile uint32_t TICK;
} watchdog_base_t;

#define WATCHDOG ((watchdog_base_t *) (0x40058000))

void watchdog_tick_start(uint32_t freq);

#endif
