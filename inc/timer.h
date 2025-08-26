#ifndef INC_TIMER_H
#define INC_TIMER_H

#include <stdint.h>

#define TIMER_BASE  0x40054000
#define TIMEHR	    0x08
#define TIMELR	    0x0c

uint64_t get_time_us();

#endif
