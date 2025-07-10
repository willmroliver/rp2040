#include <stdint.h>

#define SIO_BASE 0xd0000000
#define GPIO_IN (*((volatile unsigned long *)(SIO_BASE + 0x004)))
#define GPIO_OUT (*((volatile unsigned long *)(SIO_BASE + 0x010)))
#define GPIO_OUT_SET (*((volatile unsigned long *)(SIO_BASE + 0x014)))
#define GPIO_OUT_CLR (*((volatile unsigned long *)(SIO_BASE + 0x018)))
#define GPIO_OUT_XOR (*((volatile unsigned long *)(SIO_BASE + 0x01c)))
#define GPIO_OE (*((volatile unsigned long *)(SIO_BASE + 0x020)))
#define GPIO_OE_SET (*((volatile unsigned long *)(SIO_BASE + 0x024)))
#define GPIO_OE_CLR (*((volatile unsigned long *)(SIO_BASE + 0x028)))

#define IO_BANK0_BASE 0x40014000
#define GPIO_CTRL(io) (*((volatile unsigned long *)(IO_BANK0_BASE + 8*io + 4)))
#define GPIO_FUNCSEL_SIO 0x5 

#define RESETS_BASE 0x4000c000
#define RESETS_RESET (*((volatile unsigned long *)(RESETS_BASE + 0x0)))
#define RESETS_DONE (*((volatile unsigned long *)(RESETS_BASE + 0x8)))

typedef unsigned int u32;
typedef char u8;
typedef int i32;

void blink();
uint64_t get_time_us();

void init_io(u32 mask);
void init_gpio(u8 io);
u32 *reg_get(u32 base, u32 offset);
u32 *sio_reg_get(u32 offset);
u32 *reset_reg_get(u32 offset);
u32 *gpio_ctrl(u8 io);
void funcsel(u8 io, u32 fn);
void gpio_put(u8 io, u8 val);

int main() 
{
	blink();
}

void blink() 
{
	const u8 IO_BANK0 = 5;
	const u8 LED = 25;

	volatile uint64_t delay_us = 250000, end;

	init_io((1 << IO_BANK0));
	funcsel(LED, GPIO_FUNCSEL_SIO);
	init_gpio(LED);
	gpio_put(LED, 1);

	while (1) {
		gpio_put(LED, 1);
		end = get_time_us() + delay_us;
		while (get_time_us() < end);
		gpio_put(LED, 0);
		end = get_time_us() + delay_us;
		while (get_time_us() < end);
	}
}

void init_io(u32 mask)
{
	RESETS_RESET &= ~mask;
	while (!(RESETS_DONE & mask));
}

void init_gpio(u8 io)
{ 
	GPIO_OE_SET = (1 << io);
}

u32 *reg_get(u32 base, u32 offset)
{
	return (u32*)(base + offset);
}

void funcsel(u8 io, u32 fn) 
{
	GPIO_CTRL(io) = fn;
}

void gpio_put(u8 io, u8 val)
{
	if (val) {
		GPIO_OUT_SET = (1 << io);
	} else {
		GPIO_OUT_CLR = (1 << io);
	}
}
