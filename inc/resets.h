#ifndef INC_RESETS_H
#define INC_RESETS_H

#include <stdint.h>

/* reset subsystem control registers */
typedef struct {
	volatile uint32_t RESET;
	volatile uint32_t WDSEL;
	volatile uint32_t DONE;
} resets_base_t;

/* control register bit offsets for peripherals in the resets subsystem */
typedef uint32_t resets_target_t;

#define RESETS ((resets_base_t *)(0x4000c000))

#define RESETS_IO_BANK0 ((resets_target_t)(5))

void init_peripheral(resets_target_t mask);

#endif
