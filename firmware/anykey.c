#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "v-usb/usbdrv/usbdrv.h"
#include "usbconfig.h"
#include "anykey.h"

/** HID report */
static struct anykey_report report;

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

	/* Enable pull-up resistors */
	KEY_PORTX = KEY_BITS;

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

		/* Read keys */
		report.keys = ( ( ~KEY_PINX ) & KEY_BITS );

		/* Poll USB */
		usbPoll();

		/* Return interrupt report if applicable */
		if ( usbInterruptIsReady() ) {
			usbSetInterrupt ( ( void * ) &report,
					  sizeof ( report ) );
		}
	}
}
