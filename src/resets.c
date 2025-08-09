#include "resets.h"

void init_peripheral(resets_target_t target)
{
	target = 1 << target; 
	
	/* De-assert peripheral service from reset state */
	RESETS->RESET &= ~target; 

	/* wait for ready-signal from peripheral  */
	while (!(RESETS->DONE & target));
}

