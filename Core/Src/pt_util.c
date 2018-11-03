/*
 * pt_util.c
 *
 *  Created on: Oct 20, 2018
 *      Author: wuyua
 */
#include "pt_util.h"
#include "pt/pt.h"
PT_THREAD(pt_delay_tick(struct pt_time *pt, uint32_t time_ms))
{
	PT_BEGIN(pt->pt);
	PT_YIELD_UNTIL(pt->pt, TICK_FUNCTION() - pt->tick_starting > time_ms);
	PT_END(pt->pt);
}
