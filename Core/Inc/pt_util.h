/*
 * pt_util.h
 *
 *  Created on: Oct 20, 2018
 *      Author: wuyua
 */

#ifndef INC_PT_UTIL_H_
#define INC_PT_UTIL_H_

#include "stm32f1xx_hal.h"
#include "pt/pt.h"
#include "concat.h"
#define TICK_FUNCTION HAL_GetTick	// By default, the tick is 1 ms

struct pt_time {
	struct pt* pt;
	uint32_t tick_starting;
};

PT_THREAD(pt_delay_tick(struct pt_time *pt, uint32_t time_ms));

#define PT_TIME_CREATE(NAME) CONCAT2(static struct pt _pt_, __LINE__); \
static struct pt_time NAME;\
PT_INIT(CONCAT2(&_pt_, __LINE__));\
NAME.pt = CONCAT2(&_pt_,__LINE__)

#define PT_TIME_DELAY_TICK(PT, TIME) \
do { \
	static struct pt CONCAT2(_pt_, __LINE__); \
	static struct pt_time CONCAT2(_pt_time_, __LINE__);\
	PT_INIT(CONCAT2(&_pt_, __LINE__));\
	CONCAT2(_pt_time_, __LINE__).pt = CONCAT2(&_pt_,__LINE__); \
	CONCAT2(_pt_time_, __LINE__).tick_starting = TICK_FUNCTION(); \
	PT_WAIT_THREAD(PT, pt_delay_tick(&CONCAT2(_pt_time_, __LINE__), TIME)); \
} while(0)

#define PT_TIME_DELAY_TICK_REUSED(PT, PT_SUB, TIME)
#endif /* INC_PT_UTIL_H_ */
