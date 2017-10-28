#include <avr/io.h>
#include <avr/interrupt.h>
#include "anykey.h"
#include "tiny8.h"

/**
 * Initialise board
 *
 */
void init_board ( void ) {

	/* Enable pull-up resistors */
	PORTB = ( _BV ( PB5 ) | _BV ( PB4 ) | _BV ( PB3 ) | _BV ( PB0 ) );

	/* Enable pin change interrupts */
	PCMSK = ( _BV ( PCINT5 ) | _BV ( PCINT4 ) | _BV ( PCINT3 ) |
		  _BV ( PCINT0 ) );
	GIMSK |= _BV ( PCIE );
}

/**
 * Handle pin change interrupt
 *
 */
ISR ( PCINT0_vect ) {
	uint8_t pins;

	/* Read (inverted) pin state */
	pins = ~PINB;

	/* Eliminate unused bits */
	report.keys = ( ( ( pins & ( _BV ( PB5 ) | _BV ( PB4 ) |
				     _BV ( PB3 ) ) ) >> ( PB3 - 1 ) ) |
			( ( pins & _BV ( PB0 ) ) >> ( PB0 - 0 ) ) );
}
