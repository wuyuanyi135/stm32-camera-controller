/*
 * task_monitor.h
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */

#ifndef INC_TASK_MONITOR_H_
#define INC_TASK_MONITOR_H_

#include "pt/pt.h"
#define TASK_MONITOR_POLL_INTERVAL 500
PT_THREAD(task_monitor_cdc_connection(struct pt* pt));

#endif /* INC_TASK_MONITOR_H_ */
