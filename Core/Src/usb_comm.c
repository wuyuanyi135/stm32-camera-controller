/*
 * usb_comm.c
 *
 *  Created on: Oct 20, 2018
 *      Author: wuyuanyi
 */
#include "pt/pt.h"
#include "usbd_cdc_if.h"
#include "string.h"
#include "pt_util.h"
#include "usb_comm.h"
#include "usb_device.h"
static int i = 0;

PT_THREAD(usb_send_daemon(struct pt* pt))
{
	uint8_t* send_buffer = "Hello World!\n";
	PT_BEGIN(pt);

	//PT_TIME_CREATE(pt_time);
	do {
//		if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) {
//			CDC_Transmit_FS(send_buffer, strlen(send_buffer));
//		}

		PT_TIME_DELAY_TICK(pt, 1000);

		i++;
	} while(1);
	PT_END(pt);
}
