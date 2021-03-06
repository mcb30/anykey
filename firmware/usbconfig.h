#ifndef _USBCONFIG_H
#define _USBCONFIG_H

/* Include per-board header file */
#define BOARD_HEADER <BOARD.h>
#include BOARD_HEADER

/** Provide an interrupt IN endpoint for HID reports */
#define USB_CFG_HAVE_INTRIN_ENDPOINT 1

/** Interrupt IN endpoint poll interval (in ms) */
#define USB_CFG_INTR_POLL_INTERVAL 10

/** Device is bus powered */
#define USB_CFG_IS_SELF_POWERED 0

/** Maximum power draw (in mA) */
#define USB_CFG_MAX_BUS_POWER 100

/* Vendor and device IDs as allowed by v-usb/usbdrv/USB-IDs-for-free.txt
 *
 * This is the vendor:device ID allocated for a HID keyboard.
 *
 */
#define USB_CFG_VENDOR_ID 0xc0, 0x16
#define USB_CFG_DEVICE_ID 0xdb, 0x27

/** Device version (1.0) */
#define USB_CFG_DEVICE_VERSION 0x00, 0x01

/* Device class (n/a) */
#define USB_CFG_DEVICE_CLASS 0
#define USB_CFG_DEVICE_SUBCLASS 0

/* Interface class (generic HID) */
#define USB_CFG_INTERFACE_CLASS 3
#define USB_CFG_INTERFACE_SUBCLASS 0
#define USB_CFG_INTERFACE_PROTOCOL 0

/** Use our configuration descriptor */
#define USB_CFG_DESCR_PROPS_CONFIGURATION USB_PROP_IS_DYNAMIC

/** Use our HID descriptor */
#define USB_CFG_DESCR_PROPS_HID USB_PROP_IS_DYNAMIC

/** Use our HID report descriptor */
#define USB_CFG_DESCR_PROPS_HID_REPORT USB_PROP_IS_DYNAMIC

/** Vendor name */
#define USB_CFG_VENDOR_NAME 'A', 'n', 'y', 'K', 'e', 'y'

/** Vendor name length */
#define USB_CFG_VENDOR_NAME_LEN 6

/** Device name */
#define USB_CFG_DEVICE_NAME 'K', 'e', 'y', 'p', 'a', 'd'

/** Device name length */
#define USB_CFG_DEVICE_NAME_LEN 6

#endif /* _USBCONFIG_H */
