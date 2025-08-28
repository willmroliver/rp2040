#include "resets.h"
#include "util.h"

void reset_deassert(resets_target_t which)
{
	which = 1 << which; 
	if (RESETS->DONE & which)
		return;
	
	/* De-assert peripheral service from reset state */
	RESETS->RESET &= ~which; 

	/* wait for ready-signal from peripheral  */
	while (!(RESETS->DONE & which))
		noop_loop();
}

void reset_assert(resets_target_t which)
{
	/* Return peripheral service into reset state */
	RESETS->RESET |= (1 << which);
}

