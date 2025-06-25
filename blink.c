#define SIO_BASE 0xd0000000
#define GPIO_OE 0x020
#define GPIO_OE_SET 0x024
#define GPIO_OE_CLR 0x028
#define GPIO_IN 0x004
#define GPIO_OUT 0x010
#define GPIO_OUT_SET 0x014
#define GPIO_OUT_CLR 0x018
#define GPIO_OUT_XOR 0x01c

#define IO_BANK0_BASE 0x40014000
#define GPIO_FUNCSEL_SIO 0x5

#define RESETS_BASE 0x4000c000
#define RESETS_RESET 0x0
#define RESETS_DONE 0x8

typedef unsigned int u32;
typedef char u8;
typedef int i32;

void blink();

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
	volatile u32 i, spin_for = (1 << 22);
	const u8 IO_BANK0 = 5;
	const u8 LED = 25;

	init_io((1 << IO_BANK0));
	funcsel(LED, GPIO_FUNCSEL_SIO);
	init_gpio(LED);
	gpio_put(LED, 1);

	while (1) {
		gpio_put(LED, 1);
		for (i = 0; i < spin_for; i++);
		gpio_put(LED, 0);
		for (i = 0; i < spin_for; i++);
	}
}

void init_io(u32 mask)
{
	u32 *set = reset_reg_get(RESETS_RESET);
	u32 *test = reset_reg_get(RESETS_DONE);

	*set &= ~mask;
	while (!(*test & mask));
}

void init_gpio(u8 io)
{ 
	*sio_reg_get(GPIO_OE_SET) = (1 << io);
}

u32 *reg_get(u32 base, u32 offset)
{
	return (u32*)(base + offset);
}

u32 *sio_reg_get(u32 offset)
{
	return (u32*)(SIO_BASE + offset);
}

u32 *reset_reg_get(u32 offset)
{
	return (u32*)(RESETS_BASE + offset);
}

u32 *gpio_ctrl(u8 io)
{
	return (u32*)(IO_BANK0_BASE + (u32)io * 8 + 4);
}

void funcsel(u8 io, u32 fn) 
{
	*gpio_ctrl(io) = fn;
}

void gpio_put(u8 io, u8 val)
{
	u32 *sio_reg;

	if (val) {
		sio_reg = sio_reg_get(GPIO_OUT_SET);
	} else {
		sio_reg = sio_reg_get(GPIO_OUT_CLR);
	}

	*sio_reg = (1 << io);
}
