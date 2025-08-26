#include <stdint.h>

#include "timer.h"
#include "resets.h"
#include "gpio.h"

extern int div(int, int);

void blink();

int main() 
{
	init_peripheral(RESETS_IO_BANK0);
	init_peripheral(RESETS_TIMER);
	blink();
}

void blink() 
{
	volatile uint64_t delay_us = 250000, end;
	int n, i = 0;

	gpio_init_sio(GPIO_LED_PIN);
	gpio_enable_output(GPIO_LED_PIN);

	n = div(15, 3);

	while (i < n) {
		gpio_put(GPIO_LED_PIN, 1);

		end = get_time_us() + delay_us;
		while (get_time_us() < end);

		gpio_put(GPIO_LED_PIN, 0);

		end = get_time_us() + delay_us;
		while (get_time_us() < end);

		i++;
	}
}

