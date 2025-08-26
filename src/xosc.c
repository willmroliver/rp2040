#include "xosc.h"
#include "util.h"

#define XOSC_ENABLE 0xfab
#define XOSC_DISABLE 0xd1e

void xosc_init()
{
	XOSC->CTRL = 0xaa0;
	XOSC->STARTUP = 47;
	XOSC->CTRL |= (XOSC_ENABLE << 12);
	while (!(XOSC->STATUS >> 31))
		noop_loop();
}
