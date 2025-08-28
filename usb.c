#include "usb.h"
#include "led.h"

int main()
{
	led_init();
	usb_init();
	blink(1, 1000, 0);
}
