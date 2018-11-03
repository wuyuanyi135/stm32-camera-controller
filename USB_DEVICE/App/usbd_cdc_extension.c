#include "usbd_cdc_extension.h"
volatile uint8_t usbd_cdc_ext_dtr = 0;

void onSetControlLineState(uint16_t wValue)
{
	// Indicates to DCE if DTE is present or not. This signal corresponds to V.24 signal 108/2 and RS-232 signal DTR.
	usbd_cdc_ext_dtr = wValue & 0x0001;
}
