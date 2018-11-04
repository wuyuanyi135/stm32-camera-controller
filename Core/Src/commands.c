//
// Created by wuyuanyi on 04/11/18.
//

#include <stm32f1xx.h>
#include "commands.h"
#include "version.h"

void command_version_callback (command_handler* cmd, uint8_t* buffer, uint32_t length)
{
    uint8_t version[] = {VERSION_HARDWARE, VERSION_SOFTWARE};
    invoke(cmd, version);
}

void command_reset_callback (command_handler* cmd, uint8_t* buffer, uint32_t length)
{
    NVIC_SystemReset();
}


void register_commands()
{
    register_command((command_t) COMMAND_VERSION_0_2, 0, 2, command_version_callback);
    register_command((command_t) COMMAND_RESET_0_0, 0, 0, command_reset_callback);
}