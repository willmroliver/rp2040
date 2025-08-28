#include "led.h"

int main() 
{
	led_init();
	blink(5, 250, 250);
}

