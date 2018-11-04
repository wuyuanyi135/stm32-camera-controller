//
// Created by wuyuanyi on 04/11/18.
//

#include <stm32f1xx.h>
#include "usb_probe.h"

void usb_reenumerate()
{
//    // set to output mode
//    SET_BIT(GPIOA->CRH, GPIO_CRH_MODE12_1 | GPIO_CRH_MODE12_0);
//    // pull low PA12
//    CLEAR_BIT(GPIOA->ODR, GPIO_ODR_ODR12);
//
//    HAL_Delay(15);
//    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_MODE12_1 | GPIO_CRH_MODE12_0);

    GPIO_InitTypeDef gpio;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pin = GPIO_PIN_12;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_Delay(15);

    gpio.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &gpio);

}