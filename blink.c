#include <stdint.h>

#include "timer.h"
#include "gpio.h"
#include "util.h"

extern int div(int, int);

void blink();

int main() 
{
	blink();
}

void blink() 
{
	volatile uint64_t delay_us = 250000, end;
	int n, i = 0;

	gpio_init_sio(GPIO_LED_PIN);
	gpio_enable_output(GPIO_LED_PIN);

	n = div(15, 3) * 2 + 1;

	while (i < n) {
		gpio_put(GPIO_LED_PIN, i++ % 2);

		end = get_time_us() + delay_us;
		while (get_time_us() < end)
			noop_loop();
	}
}

