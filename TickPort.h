#ifndef TICKPORT_H
#define TICKPORT_H


#if defined(PLIB_PIC16)

	#include <xc.h>
	#include "Compiler.h"
	#define TICKS_PER_SECOND		((CONFIG_TIMING_MAIN_CLOCK + 128ull)/8ull)	// Timer with 1:8 prescaler

#elif defined(PLIB_PIC18)

	#include <xc.h>
	#include "Compiler.h"
	#define TICKS_PER_SECOND		((CONFIG_TIMING_MAIN_CLOCK + 128ull)/256ull)	// Timer with 1:8 prescaler

#elif defined(PLIB_PIC24)

	#include <xc.h>
	#include "Compiler.h"
	#define TICKS_PER_SECOND		((CONFIG_TIMING_MAIN_CLOCK + 128ull)/256ull)	// Timer with 1:8 prescaler

#endif



#endif
// End of Header file
