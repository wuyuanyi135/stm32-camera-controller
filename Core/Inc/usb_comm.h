/*
 * usb_comm.h
 *
 *  Created on: Oct 20, 2018
 *      Author: wuyua
 */

#ifndef INC_USB_COMM_H_
#define INC_USB_COMM_H_

#include "pt/pt.h"

PT_THREAD(usb_send_daemon(struct pt* pt));


#endif /* INC_USB_COMM_H_ */
