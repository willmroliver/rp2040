#include <stdint.h>

#define CLOCKS_BASE 0x40008000
#define TIMER_BASE  0x40054000
#define TIMEHR 0x08
#define TIMELR 0x0c

uint64_t get_time_us()
{
	uint32_t h, l;
	l = *(uint32_t*)(TIMER_BASE + TIMELR);
	h = *(uint32_t*)(TIMER_BASE + TIMEHR);

	return ((uint64_t)h << 32) + (uint64_t)l;
}
