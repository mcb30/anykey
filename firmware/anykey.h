#ifndef _ANYKEY_H
#define _ANYKEY_H

/** Concatenate strings */
#define CONCAT( x, y ) x ## y

/** Concatenate expanded strings */
#define CONCAT_EXPANDED( x, y ) CONCAT ( x, y )

/** Port to which keys are attached */
#define KEY_PORTNAME D

/** Bits within port to which keys are attached */
#define KEY_BITS ( _BV ( PD7 ) | _BV ( PD6 ) )

/** PORTx register for keys */
#define KEY_PORTX CONCAT_EXPANDED ( PORT, KEY_PORTNAME )

/** PINx register for keys */
#define KEY_PINX CONCAT_EXPANDED ( PIN, KEY_PORTNAME )

/** USB disconnection delay */
#define USB_DISCONNECT_DELAY_MS 250

/** A USB configuration descriptor */
struct usb_config_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t bMaxPower;
} __attribute__ (( packed ));

/** A USB interface descriptor */
struct usb_interface_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
} __attribute__ (( packed ));

/** A USB endpoint descriptor */
struct usb_endpoint_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} __attribute__ (( packed ));

/** A USB HID descriptor */
struct usb_hid_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;
} __attribute__ (( packed ));

/** A USB HID class descriptor */
struct usb_hid_class_descriptor {
	uint8_t bDescriptorType;
	uint16_t wDescriptorLength;
} __attribute__ (( packed ));

/** An AnyKey HID report */
struct anykey_report {
	/** Keypress bitmask */
	uint8_t keys;
} __attribute__ (( packed ));

#endif /* _ANYKEY_H */
