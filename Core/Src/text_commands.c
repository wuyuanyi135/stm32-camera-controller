//
// Created by wuyuanyi on 01/06/19.
//

#include <version.h>
#include "text_commands.h"
#include "text_command.h"
#include "string.h"
#include <stm32f1xx.h>
#include <stdlib.h>
#include <parameters.h>
#include <errno.h>
#include <trigger.h>
#include <power_control.h>

// Helper functions
void setter_uint16(const char* cmd, const char* src, uint16_t *target, uint16_t min, uint16_t max) {
  long value = strtol(src, NULL, 10);
  if (errno == ERANGE) {
    // failed to convert
    text_feedback(cmd, "failed to convert");
    return;
  }

  if (target == NULL || src == NULL) {
    text_feedback(cmd, "null ptr");
    return;
  }

  if (*src >= min && *src <= max) {
    *target = value;
    text_feedback(cmd, "ok");
  } else { 
    text_feedback(cmd, "out of range");
  }


}

// callbacks

void ping_cb(text_command *cmd) {
  text_feedback(cmd->command, "pong");
}
void ping1_cb(text_command *cmd) {
  text_feedback(cmd->command, cmd->positional_args[0]);
}

void command_version_callback(text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "version=%d.%d", VERSION_HARDWARE, VERSION_SOFTWARE);
  text_feedback(cmd->command, reply);
}

void command_reset_callback(text_command *cmd) {
  text_feedback(cmd->command, "ok");
  NVIC_SystemReset();
}

void command_set_exposure_callback(text_command *cmd) {
  setter_uint16(cmd->command, cmd->positional_args[0], &param_exposure_time, PARAM_EXPOSURE_TIME_MIN, PARAM_EXPOSURE_TIME_MAX);
}
void command_get_exposure_callback(text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "exposure=%d", param_exposure_time);
  text_feedback(cmd->command, reply);
}

void command_set_delay_callback(text_command *cmd) {
  setter_uint16(cmd->command, cmd->positional_args[0], &param_pulse_delay, PARAM_PULSE_DELAY_MIN, PARAM_PULSE_DELAY_MAX);
}
void command_get_delay_callback(text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "delay=%d", param_pulse_delay);
  text_feedback(cmd->command, reply);
}

void command_set_filter_callback(text_command *cmd) {
  setter_uint16(cmd->command, cmd->positional_args[0], &param_digital_filter, PARAM_DIGITAL_FILTER_MIN, PARAM_DIGITAL_FILTER_MAX);
}
void command_get_filter_callback(text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "filter=%d", param_digital_filter);
  text_feedback(cmd->command, reply);
}

void command_commit_parameters_callback(text_command *cmd) {
  if (trigger_state == Enabled) {
    cancel_trigger();
    configure_trigger();
    arm_trigger();
  } else {
    configure_trigger();
  }
  text_feedback(cmd->command, "ok");
}
void command_arm_trigger_callback(text_command *cmd) {
  arm_trigger();
  text_feedback(cmd->command, "trigger=1");
}
void command_cancel_trigger_callback(text_command *cmd) {
  cancel_trigger();
  text_feedback(cmd->command, "trigger=0");
}
void command_get_trigger_callback (text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "trigger=%d", trigger_state);
  text_feedback(cmd->command, reply);
}

void command_set_power_callback(text_command *cmd) {
  int power = strtol(cmd->positional_args[0], NULL, 10);
  if (errno) {
    text_feedback(cmd->command, "failed to convert");
  }
  set_power(power);
  text_feedback(cmd->command, "ok");
}
void command_get_power_callback(text_command *cmd) {
  char reply[TEXT_MAX_REPLY_BYTES];
  sprintf(reply, "power=%d", power_state);
  text_feedback(cmd->command, reply);
}

void text_register_commands() {
  text_register_command("ping", 0, ping_cb);
  text_register_command("ping1", 1, ping1_cb);

  text_register_command("version", 0, command_version_callback);
  text_register_command("reset", 0, command_reset_callback);

  text_register_command("s_exposure", 1, command_set_exposure_callback);
  text_register_command("g_exposure", 0, command_get_exposure_callback);

  text_register_command("s_delay", 1, command_set_delay_callback);
  text_register_command("g_delay", 0, command_get_delay_callback);

  text_register_command("s_filter", 1, command_set_filter_callback);
  text_register_command("g_filter", 0, command_get_filter_callback);

  text_register_command("commit", 0, command_commit_parameters_callback);

  text_register_command("arm_trigger", 0, command_arm_trigger_callback);
  text_register_command("disarm_trigger", 0, command_cancel_trigger_callback);
  text_register_command("g_trigger", 0, command_get_trigger_callback);

  //  text_register_command("s_power", 1, command_set_power_callback);
  //  text_register_command("g_power", 0, command_get_power_callback);
}