#include "pll.h"
#include "util.h"

#define PD1_BIT_OFFSET 0x10
#define PD2_BIT_OFFSET 0x0c

void pll_init(pll_base_t *pll, 
	      uint32_t refdiv, 
	      uint32_t fbdiv,
	      uint32_t pd1,
	      uint32_t pd2)
{
	pll->CS = refdiv;
	pll->FBDIV_INT = fbdiv;
	pll->PWR = 0x3 << 2;

	while (!(pll->CS >> 31))
		noop_loop();

	pll->PRIM = (pd1 << PD1_BIT_OFFSET) & (pd2 << PD2_BIT_OFFSET);
	pll->PWR = pll->PWR & ~0x8;
}
