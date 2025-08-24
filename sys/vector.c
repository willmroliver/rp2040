#include <stdint.h>

extern uintptr_t *__bss_start__, *__bss_end__, _estack[];

extern int main();

__attribute((section(".reset_handler")))
void Reset_Handler()
{
	uintptr_t *cur = __bss_start__;

	while (cur < __bss_end__) 
		*cur++ = 0;

	main();

	while (1);
}

void NMI_Handler() 
{
	return;
}

void HardFault_Handler()
{
	while (1);
}

__attribute((section(".vector")))
void *vector_table[] = {
	_estack,	
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
};

