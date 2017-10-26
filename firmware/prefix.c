#include <stdint.h>
#include <avr/pgmspace.h>
#include "v-usb/usbdrv/usbdrv.h"
#include "anykey.h"

/** HID report descriptor */
static PROGMEM const uint8_t hid_report_descriptor[] = {
