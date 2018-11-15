//
// Created by wuyuanyi on 14/11/18.
//

#include "power_control.h"
uint8_t power_state;

void set_power(uint8_t power) {
  if (READ_BIT(power, ((uint8_t) 1 << POWER_MASTER))) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    SET_BIT(power_state, ((uint8_t) 1 << POWER_MASTER));
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    CLEAR_BIT(power_state, ((uint8_t) 1 << POWER_MASTER));
  }
}