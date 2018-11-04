//
// Created by wuyuanyi on 04/11/18.
//

#ifndef STM32_CAMERA_CONTROLLER_PARAMETERS_H
#define STM32_CAMERA_CONTROLLER_PARAMETERS_H

#include "stm32f1xx.h"

#define PARAM_TIMEOUT_MAX   (50000L)   // max laser on time 50 microseconds
extern uint32_t param_exposure_time;
extern uint32_t param_timeout;

#endif //STM32_CAMERA_CONTROLLER_PARAMETERS_H
