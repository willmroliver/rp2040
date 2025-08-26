#ifndef INC_XOSC_H
#define INC_XOSC_H

#include <stdint.h>

typedef struct {
	volatile uint32_t CTRL;	    // 0x00
	volatile uint32_t STATUS;   // 0x04
	volatile uint32_t DORMANT;  // 0x08
	volatile uint32_t STARTUP;  // 0x0c
	uint32_t reserved0[3];
	volatile uint32_t COUNT;    // 0x1c
} xosc_base_t;

#define XOSC ((xosc_base_t *) (0x40024000))

void xosc_init();

#endif
