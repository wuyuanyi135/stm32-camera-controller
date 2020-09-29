//
// Created by wuyuanyi on 13/11/18.
//

#include <parameters.h>
#include "trigger.h"
#include "stm32f1xx.h"

extern TIM_HandleTypeDef htim2;
TriggerStates trigger_state = Disabled;
void arm_trigger() {
  // triggered by rising edge of exposure active
  // reset by falling edge of exposure active

  // start to monitor the input pin that triggers exposure
//  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_OnePulse_Start_IT(&htim2, TIM_CHANNEL_2);
  trigger_state = Enabled;
};

void cancel_trigger() {
  HAL_TIM_OnePulse_Stop(&htim2, TIM_CHANNEL_2);
  trigger_state = Disabled;
}

void configure_trigger() {
  __HAL_RCC_TIM2_CLK_ENABLE();
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = param_exposure_time;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_OnePulse_Init(&htim2, TIM_OPMODE_SINGLE) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  TIM_OnePulse_InitTypeDef sConfig = {
      .ICSelection = TIM_ICSELECTION_DIRECTTI,
      .ICPolarity = TIM_ICPOLARITY_FALLING,  // stm32f1 only support detecting either edge
      .ICFilter = param_digital_filter,
      .OCPolarity = param_polarity ? TIM_OCPOLARITY_LOW : TIM_OCPOLARITY_HIGH,
      .OCMode = TIM_OCMODE_PWM2,
      .Pulse = param_pulse_delay  // AT LEAST 1
  };
  HAL_TIM_OnePulse_ConfigChannel(&htim2, &sConfig, TIM_CHANNEL_2, TIM_CHANNEL_1);
}