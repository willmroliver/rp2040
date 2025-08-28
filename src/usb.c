#include "pll.h"
#include "clocks.h"
#include "usb.h"
#include "resets.h"

void usb_init()
{
	reset_deassert(RESETS_PLL_USB);
	clock_pll_usb_init();
	reset_deassert(RESETS_USBCTRL);
}

void clock_pll_usb_init()
{
	pll_init(PLL_USB, 1, 120, 6, 5);
	clock_setup(CLK_USB, 0, 0, 48000000, 1);
}
