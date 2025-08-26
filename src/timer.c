#include "timer.h"

uint64_t get_time_us()
{
	uint32_t h, l;
	l = *(uint32_t*)(TIMER_BASE + TIMELR);
	h = *(uint32_t*)(TIMER_BASE + TIMEHR);

	return ((uint64_t)h << 32) + (uint64_t)l;
}
