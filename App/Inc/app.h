//
// Created by wuyuanyi on 14/01/19.
//

#ifndef STM32_CAMERA_CONTROLLER_APP_H
#define STM32_CAMERA_CONTROLLER_APP_H
#include <stm32f1xx.h>
#include <binary_command.h>
#define APP_FUNCTION __attribute__((section(".app_text")))
#define APP_VARIABLE __attribute__((section(".app_data")))

// all app command should be put in 0x80~0xBF
#define APP_TEST_COMMAND_0_0  (command_t)(0x80)

extern char const *_app_start;

extern uint32_t APP_VARIABLE app_map_size;
extern command_handler APP_VARIABLE app_map[];

extern void APP_FUNCTION app_init();
#endif //STM32_CAMERA_CONTROLLER_APP_H
