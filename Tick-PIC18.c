#include "Tick.h"

/* Internal counter for timer interrupts */
static volatile unsigned long tickcnt = 0;
/* Total counter 6 bytes including timer register value */
static unsigned char tickbuffer[6];

static void tick_read_internal();

void tick_init()
{
	
	TMR0L = 0;
	TMR0H = 0;
	// Configure timer interrupt
	INTCON2bits.TMR0IP = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
	
    // Timer0 on, 16-bit, internal timer, 1:256 prescaler
	//
    T0CON = 0x87;
}

DWORD tick_get()
{
	tick_read_internal();
	return *((DWORD *)&tickbuffer[0]);
}

void tick_update()
{
	if( INTCONbits.TMR0IF )
	{
		tickcnt ++;
		INTCONbits.TMR0IF = 0;
	}
}

static void tick_read_internal()
{
	do
	{
		INTCONbits.TMR0IE = 1;		// Enable interrupt
		asm("nop");
		INTCONbits.TMR0IE = 0;		// Disable interrupt
		
		tickbuffer[0] = TMR0L;
		tickbuffer[1] = TMR0H;
		
		*((DWORD*) &tickbuffer[2] ) = tickcnt;
	} while( INTCONbits.TMR0IF );
	INTCONbits.TMR0IE = 1;			// Enable interrupt
}
