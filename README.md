Tick Library
====

The "Tick" library provides functions for time management, non-blocking delays and event scheduling on various microcontrollers. The library currently supports the following devices:

* PIC16F Using Timer 1
* PIC18F Using Timer 0
* PIC24FJ, PIC24HJ using Timer 1

La librería "Tick" provee funciones para el manejo de tiempos, retardos sin bloqueos y planificacion de eventos en varios microcontroladores. La librería soporta los siguientes dispositivos:

* PIC16F Using Timer 1
* PIC18F Using Timer 0
* PIC24FJ, PIC24HJ using Timer 1

Usage
====

For those who are familiar with the use of arduino millis() function the tick library should be very easy to use and understand. The main difference is that the tick library doesn´t provide a output which is callibrated to any specific time units. Compile time constants are defined to convert between tick units and seconds, hours, days, etc.

Para aquellas personas que estan familiarizadas con el uso de la funcion millis() en el entorno Arduino, la librería "Tick" debe ser bastante fácil de utilizar y de comprender. La diferencia principal es que la librería "Tick" no presenta una salida que este calibrada a una unidad de tiempo específica. Las constantes definidas en el archivo ***Tick.h*** permiten convertir entre "tikcs" del sistema y unidades de tiempo como segundos, horas, días, etc.

```
#include "tick.h"

void main()
{
	// We operate on 32 bit ints
	// unsigned int last_time = 0;
	uint32_t last_time = 0;

	// Initialize time count facilities
	tick_init();

	// Main loop
	for (;;) {
		// Check if more than half second (TICK_SECOND/2) has elapsed
		if (tick_get() - last_time >= TICK_SECOND / 2) {
			// Store the last time we toggled the led
			last_time = tick_get();
			// and do it...
			PORTAbits.RA0 ^= 1;
		}

		// Perform other tasks here inside the main loop
	}
}

/**
 * Interrupt vector implementation. Here we must update the internal counter on
 * the tick library (this is needed on PIC16 or PIC18 parts).
 */
void interrupt isr(void)
{
	// Update the system counter
	tick_update();
	// Other interrupts can be handled here
}
```
