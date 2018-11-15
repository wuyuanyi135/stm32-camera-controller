//
// Created by wuyuanyi on 14/11/18.
//

#ifndef STM32_CAMERA_CONTROLLER_POWER_CONTROL_H
#define STM32_CAMERA_CONTROLLER_POWER_CONTROL_H
#include "stm32f1xx.h"

#define POWER_MASTER  0
extern uint8_t power_state;

void set_power(uint8_t power);
#endif //STM32_CAMERA_CONTROLLER_POWER_CONTROL_H
