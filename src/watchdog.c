#include "watchdog.h"
#include "util.h"

void watchdog_tick_start(uint32_t freq)
{
	WATCHDOG->TICK |= freq;
	WATCHDOG->TICK |= (1 << 9);

	while (!(WATCHDOG->TICK & (1 << 10)))
		noop_loop();
}
