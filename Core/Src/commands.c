//
// Created by wuyuanyi on 04/11/18.
//

#ifdef USE_BINARY_COMMAND

#include <stm32f1xx.h>
#include <parameters.h>
#include <string.h>
#include <trigger.h>
#include <power_control.h>
#include "commands.h"
#include "version.h"

void command_version_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t version[] = {cmd->command, VERSION_HARDWARE, VERSION_SOFTWARE};
  invoke(cmd, version);
}

void command_reset_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  invoke(cmd, &cmd->command);
  NVIC_SystemReset();
}

void setter_uint16(const uint16_t *src, uint16_t *target, uint16_t min, uint16_t max) {
  if (target == NULL || src == NULL)
    return;

  if (*src >= min && *src <= max)
    *target = *src;
}
void setter_uint8(const uint8_t *src, uint8_t *target, uint8_t min, uint8_t max) {
  if (target == NULL || src == NULL)
    return;

  if (*src >= min && *src <= max)
    *target = *src;
}
void command_set_exposure_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  setter_uint16((const uint16_t *) buffer, &param_exposure_time, PARAM_EXPOSURE_TIME_MIN, PARAM_EXPOSURE_TIME_MAX);
  invoke(cmd, &cmd->command);
}

void command_get_exposure_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t response[5];
  response[0] = cmd->command;
  memcpy(response + 1, &param_exposure_time, sizeof(param_exposure_time));
  invoke(cmd, response);
}

void command_set_delay_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  setter_uint16((const uint16_t *) buffer, &param_pulse_delay, PARAM_PULSE_DELAY_MIN, PARAM_PULSE_DELAY_MAX);
  invoke(cmd, &cmd->command);
}

void command_get_delay_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t response[5];
  response[0] = cmd->command;
  memcpy(response + 1, &param_pulse_delay, sizeof(param_pulse_delay));
  invoke(cmd, response);
}

void command_set_filter_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  setter_uint16((const uint16_t *) buffer, &param_digital_filter, PARAM_PULSE_DELAY_MIN, PARAM_PULSE_DELAY_MAX);
  invoke(cmd, &cmd->command);
}

void command_get_filter_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t response[5];
  response[0] = cmd->command;
  memcpy(response + 1, &param_digital_filter, sizeof(param_digital_filter));
  invoke(cmd, response);
}
void command_commit_parameters_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  if (trigger_state == Enabled) {
    cancel_trigger();
    configure_trigger();
    arm_trigger();
  } else {
    configure_trigger();
  }
  invoke(cmd, &cmd->command);
}
void command_arm_trigger_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  arm_trigger();
  invoke(cmd, &cmd->command);
}
void command_cancel_trigger_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  cancel_trigger();
  invoke(cmd, &cmd->command);
}

void command_set_power_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  set_power(*buffer);
  invoke(cmd, &cmd->command);
}
void command_get_power_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t response[2];
  response[0] = cmd->command;
  memcpy(response + 1, &power_state, sizeof(power_state));
  invoke(cmd, response);
}
void command_set_polarity_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  setter_uint8(buffer, &param_polarity, PARAM_POLARITY_MIN, PARAM_POLARITY_MAX);
  invoke(cmd, &cmd->command);
}
void command_get_polarity_callback(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  uint8_t response[2];
  response[0] = cmd->command;
  memcpy(response + 1, &param_polarity, sizeof(param_polarity));
  invoke(cmd, response);
}
void register_commands() {
  register_command((command_t) COMMAND_VERSION_0_2, 0, 2, command_version_callback);
  register_command((command_t) COMMAND_RESET_0_0, 0, 0, command_reset_callback);
  register_command((command_t) COMMAND_SET_EXPOSURE_2_0, 2, 0, command_set_exposure_callback);
  register_command((command_t) COMMAND_GET_EXPOSURE_0_2, 0, 2, command_get_exposure_callback);
  register_command((command_t) COMMAND_SET_DELAY_2_0, 2, 0, command_set_delay_callback);
  register_command((command_t) COMMAND_GET_DELAY_0_2, 0, 2, command_get_delay_callback);
  register_command((command_t) COMMAND_SET_FILTER_2_0, 2, 0, command_set_filter_callback);
  register_command((command_t) COMMAND_GET_FILTER_0_2, 0, 2, command_get_filter_callback);
  register_command((command_t) COMMAND_COMMIT_PARAMETERS_0_0, 0, 0, command_commit_parameters_callback);
  register_command((command_t) COMMAND_ARM_TRIGGER_0_0, 0, 0, command_arm_trigger_callback);
  register_command((command_t) COMMAND_CANCEL_TRIGGER_0_0, 0, 0, command_cancel_trigger_callback);
  register_command((command_t) COMMAND_SET_POWER_1_0, 1, 0, command_set_power_callback);
  register_command((command_t) COMMAND_GET_POWER_0_1, 0, 1, command_get_power_callback);
  register_command((command_t) COMMAND_SET_POLARITY_1_0, 1, 0, command_set_polarity_callback);
  register_command((command_t) COMMAND_GET_POLARITY_0_1, 0, 1, command_get_polarity_callback);
}

#endif
