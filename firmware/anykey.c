#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "v-usb/usbdrv/usbdrv.h"
#include "usbconfig.h"
#include "anykey.h"

/** HID report */
struct anykey_report report;

/**
 * Handle HID-specific requests
 *
 */
usbMsgLen_t usbFunctionSetup ( uint8_t data[8] ) {
	usbRequest_t *req = ( ( void * ) data );

	if ( ( ( req->bmRequestType & USBRQ_TYPE_MASK ) == USBRQ_TYPE_CLASS ) &&
	     ( req->bRequest == USBRQ_HID_GET_REPORT ) ) {

		/* Return current report */
		usbMsgPtr = ( ( void * ) &report );
		return sizeof ( report );

	} else {

		/* Not implemented */
		return 0;

	}
}

/**
 * Main program
 *
 */
int main ( void ) {
	uint8_t i;

	/* Reset watchdog */
	wdt_enable ( WDTO_1S );

	/* Perform board-specific initialisation */
	init_board();

	/* Initialise V-USB library */
	usbInit();

	/* Fake USB disconnect/reconnect */
	usbDeviceDisconnect();
	for ( i = 0 ; i < USB_DISCONNECT_DELAY_MS ; i++ ) {
		wdt_reset();
		_delay_ms ( 1 );
	}
	usbDeviceConnect();

	/* Enable interrupts */
	sei();

	/* Main loop */
	while ( 1 ) {

		/* Kick watchdog */
		wdt_reset();

		/* Poll USB */
		usbPoll();

		/* Return interrupt report if applicable */
		if ( usbInterruptIsReady() ) {
			usbSetInterrupt ( ( void * ) &report,
					  sizeof ( report ) );
		}

		/* Go back to sleep */
		sleep_mode();
	}
}
