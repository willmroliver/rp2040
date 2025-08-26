#include "util.h"

void noop_loop()
{
	__asm volatile("nop");
}

void noop_for(int n)
{
	for (; n; n--)
		noop_loop();
}
