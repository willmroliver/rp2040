#ifndef INC_SIO_H
#define INC_SIO_H

#include <stdint.h>

typedef struct {
	volatile uint32_t CPUID;	// 0x0
	volatile uint32_t GPIO_IN;	// 0x4
	volatile uint32_t GPIO_HI_IN;	// 0x8
	volatile uint32_t _reserved0;
	volatile uint32_t GPIO_OUT;	// 0x10
	volatile uint32_t GPIO_OUT_SET;	// 0x14
	volatile uint32_t GPIO_OUT_CLR; // 0x18
	volatile uint32_t GPIO_OUT_XOR;	// 0x1c
	volatile uint32_t GPIO_OE;	// 0x20
	volatile uint32_t GPIO_OE_SET;	// 0x24
	volatile uint32_t GPIO_OE_CLR;	// 0x28
	volatile uint32_t GPIO_OE_XOR;	// 0x2c
} sio_base_t;

#define SIO ((sio_base_t *) (0xd0000000))

#endif
