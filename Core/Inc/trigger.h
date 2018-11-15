//
// Created by wuyuanyi on 13/11/18.
//

#ifndef STM32_CAMERA_CONTROLLER_TRIGGER_H
#define STM32_CAMERA_CONTROLLER_TRIGGER_H
#include "stm32f1xx.h"
typedef enum {
  Enabled,
  Disabled
} TriggerStates;
extern TriggerStates trigger_state;
void arm_trigger();
void cancel_trigger();
void configure_trigger();
#endif //STM32_CAMERA_CONTROLLER_TRIGGER_H
