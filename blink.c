#include <stdint.h>

#include "clocks.h"
#include "resets.h"
#include "gpio.h"

void blink();

extern int div(int, int);

int main() 
{
	init_peripheral(RESETS_IO_BANK0);
	blink();
}

void blink() 
{
	volatile uint64_t delay_us = 500000, end;
	int n, i = 0;

	gpio_init_sio(GPIO_LED_PIN);
	gpio_enable_output(GPIO_LED_PIN);

	n = div(10, 3);

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

