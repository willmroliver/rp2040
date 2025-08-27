#include <stdint.h>
#include "pll.h"
#include "resets.h"
#include "util.h"
#include "watchdog.h"
#include "xosc.h"
#include "clocks.h"

extern uintptr_t *__bss_start__, *__bss_end__, _estack[];

extern int main();

__attribute((section(".reset_handler")))
void Reset_Handler()
{
	uintptr_t *cur = __bss_start__;

	while (cur < __bss_end__) 
		*cur++ = 0;

	reset_deassert(RESETS_IO_BANK0);
	reset_deassert(RESETS_TIMER);
	reset_deassert(RESETS_PLL_SYS);

	xosc_init();
	clock_setup(CLK_REF, 2, 0, 12000000, 1);
	clock_setup(CLK_SYS, 0, 0, 12000000, 1);
	clock_setup(CLK_PERI, 0, 0, 12000000, 1);
	pll_init(PLL_SYS, 1, 125, 6, 2);

	/* set system clock to use XOSC + PLL at 125MHz */
	clock_setup(CLK_SYS, 1, 0, 125000000, 1);
	watchdog_tick_start(12);

	main();

	while (1);
}

void NMI_Handler() 
{
	return;
}

void HardFault_Handler()
{
	while (1);
}

__attribute((section(".vector")))
void *vector_table[] = {
	_estack,	
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
};

