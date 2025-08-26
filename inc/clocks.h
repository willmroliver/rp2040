#ifndef INC_CLOCKS_H
#define INC_CLOCKS_H

#include <stdint.h>

typedef struct {
	volatile uint32_t GPOUT0_CTRL;	    // 0x00	
	volatile uint32_t GPOUT0_DIV;	    // 0x04	
	volatile uint32_t GPOUT0_SELECTED;  // 0x08	
	volatile uint32_t GPOUT1_CTRL;	    // 0x0c	
	volatile uint32_t GPOUT1_DIV;	    // 0x10	
	volatile uint32_t GPOUT1_SELECTED;  // 0x14	
	volatile uint32_t GPOUT2_CTRL;	    // 0x18	
	volatile uint32_t GPOUT2_DIV;	    // 0x1c	
	volatile uint32_t GPOUT2_SELECTED;  // 0x20	
	volatile uint32_t GPOUT3_CTRL;	    // 0x24	
	volatile uint32_t GPOUT3_DIV;	    // 0x28	
	volatile uint32_t GPOUT3_SELECTED;  // 0x2c	
	volatile uint32_t REF_CTRL;	    // 0x30	
	volatile uint32_t REF_DIV;	    // 0x34	
	volatile uint32_t REF_SELECTED;	    // 0x38	
	volatile uint32_t SYS_CTRL;	    // 0x3c	
	volatile uint32_t SYS_DIV;	    // 0x40	
	volatile uint32_t SYS_SELECTED;	    // 0x44	
} clocks_base_t;

typedef struct {
	volatile uint32_t ctrl;
	volatile uint32_t div;
	volatile uint32_t selected;
} clocks_generic_t;

typedef enum {
	CLK_GPOUT0 = 0,
	CLK_GPOUT1,
	CLK_GPOUT2,
	CLK_GPOUT3,
	CLK_REF,
	CLK_SYS,
	CLK_PERI,
} clocks_t;

#define NUM_CLOCKS 6 
#define CLOCKS ((clocks_base_t *) (0x40008000))
#define CLOCK(n) ((clocks_generic_t *) ((uintptr_t)(CLOCKS) + (0xc * n)))

int has_glitchless_mux(clocks_t which);

void clock_setup(clocks_t which,
		      uint32_t src,
		      uint32_t aux,
		      uint32_t freq,
		      uint32_t div);

void clock_switch_src(clocks_t which, uint32_t src);

void clock_switch_aux(clocks_t which, uint32_t aux);

#endif
