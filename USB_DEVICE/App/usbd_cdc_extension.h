/*
 * usbd_cdc_extension.h
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */

#ifndef APP_USBD_CDC_EXTENSION_H_
#define APP_USBD_CDC_EXTENSION_H_
#include "stdint.h"

extern volatile uint8_t usbd_cdc_ext_dtr;

void onSetControlLineState(uint16_t wValue);

#endif /* APP_USBD_CDC_EXTENSION_H_ */
