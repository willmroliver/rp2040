#ifndef INC_GPIO_H
#define INC_GPIO_H

#include <stdint.h>

#define IO_BANK0_BASE 0x40014000

#define GPIO_CTRL(pin) (*((volatile unsigned long *)(IO_BANK0_BASE + 8*pin + 4)))

#define GPIO_FUNCSEL_SIO 5

#define GPIO_LED_PIN 25

void gpio_init_sio(uint8_t pin);

void gpio_enable_output(uint8_t pin);

void gpio_put(uint8_t pin, int val);

void gpio_clear(uint8_t pin);

int gpio_in(uint8_t pin);

int gpio_out(uint8_t pin);

#endif
