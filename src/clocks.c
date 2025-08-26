#include "clocks.h"
#include "util.h"

#define REF_SYS_AUX_SRC 0x1 
#define AUX_SRC_BIT_OFFSET 0x5 

static uint32_t configured_freq[NUM_CLOCKS];

int has_glitchless_mux(clocks_t which)
{
	return which == CLK_REF || which == CLK_SYS;
}

void clock_setup(clocks_t which,
		      uint32_t src,
		      uint32_t aux,
		      uint32_t freq,
		      uint32_t div)
{
	div <<= 8;

	int glitchless = has_glitchless_mux(which);

	clocks_generic_t *clock = CLOCK(which);

	/* if new divisor is greater, set the div before source, */
	/* otherwise wait: avoids temp over-speed */
	if (div > clock->div)
		clock->div = div;
	
	/* if glitchless (ref || sys) and changing aux mux, */
	/* must first switch away from aux src */
	if (glitchless && src == REF_SYS_AUX_SRC) {
		clock->ctrl &= ~0x3;

		while (!(clock->selected & 1u))
			noop_loop();
	} 
	/* else stop the clock to avoid glitches */
	else if (!glitchless) {
		/* clear the ENABLE flag then delay 4 cycles of target clock */
		clock->ctrl &= ~(1 << 11);

		uint32_t delay_cycles = 4 * (configured_freq[CLK_SYS] 
			/ configured_freq[which] + 1);

		noop_for(delay_cycles);
	}

	clock->ctrl &= (~(0x1f << AUX_SRC_BIT_OFFSET))
		| (aux << AUX_SRC_BIT_OFFSET);

	if (glitchless) {
		clock->ctrl = (clock->ctrl & ~0x1f) | src;
		while (!(clock->selected & (1 << src)))
			noop_loop();
	}

	clock->ctrl |= (1 << 11);
	clock->div = div;
	configured_freq[which] = freq;
} 

void clock_switch_src(clocks_t which, uint32_t src)
{
	clocks_generic_t *clk = CLOCK(which);
	clk->ctrl &= (~0x1f) | src;
	while (!(clk->selected & (1 << src)))
		noop_loop();
}

void clock_switch_aux(clocks_t which, uint32_t aux)
{
	clocks_generic_t *clk = CLOCK(which);
	clk->ctrl &= (~(0x1f << AUX_SRC_BIT_OFFSET))
		| (aux << AUX_SRC_BIT_OFFSET);
}
