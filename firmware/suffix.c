};

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __le16(x) (x)
#else
#error "Compiler is not using little endian convention for AVR"
#endif

/** Configuration descriptor */
static PROGMEM const struct {
	struct usb_config_descriptor config;
	struct usb_interface_descriptor interface;
	struct {
		struct usb_hid_descriptor hid;
		struct usb_hid_class_descriptor class;
	} __attribute__ (( packed )) hid;
	struct usb_endpoint_descriptor endpoint;
} __attribute__ (( packed )) config_descriptor = {
	.config = {
		.bLength = sizeof ( config_descriptor.config ),
		.bDescriptorType = USBDESCR_CONFIG,
		.wTotalLength = __le16 ( sizeof ( config_descriptor ) ),
		.bNumInterfaces = 1,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		.bmAttributes = ( 0x80 | USBATTR_REMOTEWAKE ),
		.bMaxPower = ( USB_CFG_MAX_BUS_POWER / 2 ),
	},
	.interface = {
		.bLength = sizeof ( config_descriptor.interface ),
		.bDescriptorType = USBDESCR_INTERFACE,
		.bInterfaceNumber = 0,
		.bAlternateSetting = 0,
		.bNumEndpoints = 1,
		.bInterfaceClass = USB_CFG_INTERFACE_CLASS,
		.bInterfaceSubClass = USB_CFG_INTERFACE_SUBCLASS,
		.bInterfaceProtocol = USB_CFG_INTERFACE_PROTOCOL,
		.iInterface = 0,
	},
	.hid = {
		.hid = {
			.bLength = sizeof ( config_descriptor.hid ),
			.bDescriptorType = USBDESCR_HID,
			.bcdHID = 0x0101 /* Version 1.1 */,
			.bCountryCode = 0,
			.bNumDescriptors = 1,
		},
		.class = {
			.bDescriptorType = USBDESCR_HID_REPORT,
			.wDescriptorLength =
			      __le16 ( sizeof ( hid_report_descriptor ) ),
		},
	},
	.endpoint = {
		.bLength = sizeof ( config_descriptor.endpoint ),
		.bDescriptorType = USBDESCR_ENDPOINT,
		.bEndpointAddress = 0x81 /* EP 1 IN */,
		.bmAttributes = 0x03 /* Interrupt */,
		.wMaxPacketSize = __le16 ( 8 ),
		.bInterval = USB_CFG_INTR_POLL_INTERVAL,
	},
};

/**
 * Get descriptor
 *
 */
usbMsgLen_t usbFunctionDescriptor ( usbRequest_t *req ) {
	uint8_t desc = req->wValue.bytes[1];

	if ( desc == USBDESCR_CONFIG ) {

		/* Return configuration descriptor */
		usbMsgPtr = ( ( void * ) &config_descriptor );
		return ( sizeof ( config_descriptor) );

	} else if ( desc == USBDESCR_HID ) {

		/* Return HID descriptor */
		usbMsgPtr = ( ( void * ) &config_descriptor.hid );
		return ( sizeof ( config_descriptor.hid ) );

	} else if ( desc == USBDESCR_HID_REPORT ) {

		/* Return HID report descriptor */
		usbMsgPtr = ( ( void * ) hid_report_descriptor );
		return ( sizeof ( hid_report_descriptor ) );

	} else {

		/* Not implemented */
		return 0;

	}
}
