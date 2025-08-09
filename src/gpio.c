#include "sio.h"
#include "gpio.h"

void gpio_init_sio(uint8_t pin)
{
	GPIO_CTRL(pin) = GPIO_FUNCSEL_SIO;
}

void gpio_enable_output(uint8_t pin)
{
	SIO->GPIO_OE_SET = (1 << pin);
}

void gpio_put(uint8_t pin, int val)
{
	if (val) {
		SIO->GPIO_OUT_SET = (1 << pin);
	} else {
		SIO->GPIO_OUT_CLR = (1 << pin);
	}
}

void gpio_clear(uint8_t pin)
{ 
	SIO->GPIO_OUT_CLR = (1 << pin);
}

int gpio_in(uint8_t pin)
{
	return SIO->GPIO_IN & (1 << pin);
}

int gpio_out(uint8_t pin)
{
	return SIO->GPIO_OUT & (1 << pin);
}
