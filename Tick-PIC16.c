#include "Tick.h"

/* Internal counter for timer interrupts */
static volatile unsigned long tickcnt = 0;
/* Total counter 6 bytes including timer register value */
static unsigned char tickbuffer[6];

static void tick_read_internal();

void tick_init()
{
	T1CON = 0;
	TMR1L = 0;
	TMR1H = 0;
	// Configure timer interrupts
	PIR1bits.TMR1IF = 0;
	PIE1bits.TMR1IE = 1;
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	// Internal clock, 1:8 prescaler, timer enabled
	T1CON = 0x31;
}

DWORD tick_get()
{
	tick_read_internal();
	return *((DWORD *) & tickbuffer[0]);
}

void tick_update()
{
	if (PIR1bits.TMR1IF) {
		tickcnt++;
		PIR1bits.TMR1IF = 0;
	}
}

static void tick_read_internal()
{
	do {
		PIE1bits.TMR1IE = 1; // Enable interrupt
		asm("nop");
		PIE1bits.TMR1IE = 0; // Disable interrupt

		tickbuffer[0] = TMR1L;
		tickbuffer[1] = TMR1H;

		*((DWORD*) & tickbuffer[2]) = tickcnt;
	} while (PIR1bits.TMR1IF);
	PIE1bits.TMR1IE = 1;
}
