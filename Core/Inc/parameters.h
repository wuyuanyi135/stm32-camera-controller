//
// Created by wuyuanyi on 04/11/18.
//

#ifndef STM32_CAMERA_CONTROLLER_PARAMETERS_H
#define STM32_CAMERA_CONTROLLER_PARAMETERS_H

#include "stm32f1xx.h"

#define PARAM_DIGITAL_FILTER_MIN  0
#define PARAM_DIGITAL_FILTER_MAX  0xffff
extern uint16_t param_digital_filter;

#define PARAM_PULSE_DELAY_MIN  1
#define PARAM_PULSE_DELAY_MAX  0xffff
extern uint16_t param_pulse_delay;

#define PARAM_EXPOSURE_TIME_MIN 0
#define PARAM_EXPOSURE_TIME_MAX 0xffff
extern uint16_t param_exposure_time;

#define PARAM_POLARITY_MIN 0
#define PARAM_POLARITY_MAX 1
extern uint8_t  param_polarity;
#endif //STM32_CAMERA_CONTROLLER_PARAMETERS_H
