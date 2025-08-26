#ifndef INC_PLL_H
#define INC_PLL_H

#include <stdint.h>

typedef struct {
	volatile uint32_t CS;
	volatile uint32_t PWR;
	volatile uint32_t FBDIV_INT;
	volatile uint32_t PRIM;
} pll_base_t;

#define PLL_SYS ((pll_base_t *) (0x40028000))
#define PLL_USB ((pll_base_t *) (0x4002c000))

void pll_init(pll_base_t *pll, 
	      uint32_t refdiv, 
	      uint32_t fbdiv,
	      uint32_t pd1,
	      uint32_t pd2);

#endif


