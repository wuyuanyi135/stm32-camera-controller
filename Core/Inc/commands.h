//
// Created by wuyuanyi on 04/11/18.
//

#ifndef STM32_CAMERA_CONTROLLER_COMMANDS_H
#define STM32_CAMERA_CONTROLLER_COMMANDS_H

#include "binary_command.h"

// Command definitions:
// Name convention: COMMAND_ARGINBYTES_ARGOUTBYTES

#define COMMAND_VERSION_0_2 (0x20)
#define COMMAND_RESET_0_0   (0x35)

#define COMMAND_ARM_TRIGGER_0_0 (0x40)
#define COMMAND_CANCEL_TRIGGER_0_0 (0x41)

#define COMMAND_SET_TIMEOUT_4_0 (0x42)
#define COMMAND_GET_TIMEOUT_0_4 (0x43)

#define COMMAND_SET_EXPOSURE_4_0 (0x44)
#define COMMAND_GET_EXPOSURE_0_4 (0x45)

/* return the last error. frame structure:
 * 0-3: millisecond timestamp. zero if no error occured
 * 4-7: error id
 * 8-11: error args
 */
#define COMMAND_GET_LAST_ERROR_0_12 (0x50)

// TODO: auto error report

/*
 * Register the commands
 */
void register_commands();


#endif //STM32_CAMERA_CONTROLLER_COMMANDS_H
