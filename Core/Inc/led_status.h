/*
 * led_status.h
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */

#ifndef INC_LED_STATUS_H_
#define INC_LED_STATUS_H_

#include "pt/pt.h"
#include "stdint.h"

#define LED_PIN GPIO_PIN_13
#define LED_PIN_GROUP GPIOC
#define LED_ON	0
#define LED_OFF 1

/**
 * Control functions
 */
void led_always(uint8_t state);

/**
 * Strobe the led
 * @param sequence_ms strobing sequence in ms. The format should be:
 * [
 * 	on_for_ms, off_for_ms,
 * 	...
 * ]
 * @param repeat repeat count. Zero for infinite
 */
void led_strobe(uint32_t* sequence_ms,uint32_t buffer_size, uint32_t repeat);

void led_init();

/**
 * Run this task for strobing LED.
 * This thread will not exit. It will be stopped by led_always function
 * @param PT_THREAD(task_led_strobe(struct pt* pt))
 * @return
 */
PT_THREAD(task_led_strobe());
#endif /* INC_LED_STATUS_H_ */
