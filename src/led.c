#include "timer.h"
#include "gpio.h"
#include "util.h"
#include "led.h"

void led_init()
{
	gpio_init_sio(GPIO_LED_PIN);
	gpio_enable_output(GPIO_LED_PIN);
}

void blink(int n, unsigned on_ms, unsigned off_ms)
{
	volatile uint64_t end;
	int i = 0; 

	on_ms *= 1e3;
	off_ms *= 1e3;
	
	while (i < n) {
		/* @todo - use alarms / something async for the delays */

		end = get_time_us() + off_ms;
		while (get_time_us() < end)
			noop_loop();

		gpio_put(GPIO_LED_PIN, 1);

		end = get_time_us() + on_ms;
		while (get_time_us() < end)
			noop_loop();

		gpio_put(GPIO_LED_PIN, 0);

		i++;
	}
}
