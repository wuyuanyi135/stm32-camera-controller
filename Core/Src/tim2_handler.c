//
// Created by wuyuanyi on 13/11/18.
//

#include "tim2_handler.h"
#include "stm32f1xx.h"

extern TIM_HandleTypeDef htim2;

void TIM2_IRQHandler() {
  HAL_TIM_IRQHandler(&htim2);
}