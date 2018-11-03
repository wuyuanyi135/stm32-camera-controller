/*
 * led_status.c
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */

#include "led_status.h"
#include "stm32f1xx_hal.h"
#include "pt/pt.h"
#include "pt_util.h"
#include "string.h"
#define LED_STROBE_BUFFER_SIZE 10
#define STOPPED	0
#define RUNNING	1

static uint32_t _strobe_buffer[LED_STROBE_BUFFER_SIZE * 2];
static uint32_t _repeat;
static uint32_t _repeat_count;
static uint32_t _length;
static uint8_t _task_status;
static struct pt _task_pt;

void led_init()
{
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pin = GPIO_PIN_13;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	gpio.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(LED_PIN_GROUP, &gpio);

	_task_status = STOPPED;
	_repeat = 0;
	_repeat_count = 0;

	PT_INIT(&_task_pt);
}

void led_always(uint8_t state)
{
	HAL_GPIO_WritePin(LED_PIN_GROUP, LED_PIN, state);
	_task_status = STOPPED;
}

void led_strobe(uint32_t* sequence_ms, uint32_t count, uint32_t repeat)
{
	memcpy(_strobe_buffer, sequence_ms, count*sizeof(uint32_t));
	_repeat = repeat;
	_repeat_count = 0;
	_task_status = RUNNING;
	_length = count;
	PT_INIT(&_task_pt);
}

PT_THREAD(task_led_strobe())
{
	static uint32_t on_time, off_time;
	static uint32_t index;
	// dirty modification to guard no-execution when turned off.
	if (_task_status == STOPPED)
		return PT_YIELDED;

	PT_BEGIN(&_task_pt);
	index = 0;

	while (1)
	{
		if (index >= _length)
		{
			// a cycle has been finished
			index = 0;

			if (_repeat != 0)
			{
				// when repeat is enabled

				if (_repeat_count < _repeat)
				{
					_repeat_count++;
				}
				else
				{
					_task_status = STOPPED;
					_repeat_count = 0;
					PT_RESTART(&_task_pt);
				}
			}
		}

		on_time = _strobe_buffer[index++];
		off_time = _strobe_buffer[index++];

		HAL_GPIO_WritePin(LED_PIN_GROUP, LED_PIN, LED_ON);
		PT_TIME_DELAY_TICK(&_task_pt, on_time);

		HAL_GPIO_WritePin(LED_PIN_GROUP, LED_PIN, LED_OFF);
		PT_TIME_DELAY_TICK(&_task_pt, off_time);
	}

PT_END(&_task_pt);
}
