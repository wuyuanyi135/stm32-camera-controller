//
// Created by wuyuanyi on 04/11/18.
//

#include <stm32f1xx.h>
#include <parameters.h>
#include <string.h>
#include "commands.h"
#include "version.h"

void command_version_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  uint8_t version[] = {cmd->command, VERSION_HARDWARE, VERSION_SOFTWARE};
  invoke (cmd, version);
}

void command_reset_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  invoke (cmd, &cmd->command);
  NVIC_SystemReset ();
}

void command_set_exposure_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  uint32_t tmp_exposure_time;
  memcpy (&tmp_exposure_time, buffer, cmd->bytes_args);

  if (tmp_exposure_time <= param_timeout)
    {
      param_exposure_time = tmp_exposure_time;
    }
  // else: the exposure configuration is invalid. Discard this set request
  invoke (cmd, &cmd->command);
}

void command_get_exposure_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  uint8_t response[5];
  response[0] = cmd->command;
  memcpy (response + 1, &param_exposure_time, sizeof (param_exposure_time));
  invoke (cmd, response);
}

void command_set_timeout_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  uint32_t tmp_timeout;
  memcpy (&tmp_timeout, buffer, cmd->bytes_args);

  if (tmp_timeout <= PARAM_TIMEOUT_MAX)
    {

      param_timeout = tmp_timeout;

      if (param_timeout < param_exposure_time)
        {
          // if the actual exposure time is less than the max, modify it.
          param_exposure_time = param_timeout;
        }
    }

  invoke (cmd, &cmd->command);
}

void command_get_timeout_callback (command_handler *cmd, uint8_t *buffer, uint32_t length)
{
  uint8_t response[5];
  response[0] = cmd->command;
  memcpy (response + 1, &param_timeout, sizeof (param_timeout));
  invoke (cmd, response);
}

void register_commands ()
{
  register_command ((command_t) COMMAND_VERSION_0_2, 0, 2, command_version_callback);
  register_command ((command_t) COMMAND_RESET_0_0, 0, 0, command_reset_callback);
  register_command ((command_t) COMMAND_SET_EXPOSURE_4_0, 4, 0, command_set_exposure_callback);
  register_command ((command_t) COMMAND_GET_EXPOSURE_0_4, 0, 4, command_get_exposure_callback);
  register_command ((command_t) COMMAND_SET_TIMEOUT_4_0, 4, 0, command_set_timeout_callback);
  register_command ((command_t) COMMAND_GET_TIMEOUT_0_4, 0, 4, command_get_timeout_callback);
}