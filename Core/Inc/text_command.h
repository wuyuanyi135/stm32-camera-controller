//
// Created by wuyuanyi on 31/05/19.
//

#ifndef STM32_CAMERA_CONTROLLER_TEXT_COMMAND_H
#define STM32_CAMERA_CONTROLLER_TEXT_COMMAND_H

#include "ringbuffer.h"
#include "pt/pt.h"

#define TEXT_MAX_REPLY_BYTES 128
#define TEXT_COMMAND_TABLE_SIZE    32
#define TEXT_COMMAND_OK 1
#define TEXT_COMMAND_FAILED 0

#define TEXT_COMMAND_LENGTH_MAX 16

#define TEXT_ERROR_OK 0
#define TEXT_ERROR_INVALID_COMMAND 2
#define TEXT_ERROR_NO_LF 3
#define TEXT_ERROR_NULL_PTR 4

extern ring_buffer_t text_recv_buffer;

typedef struct text_command_handler text_command_handler; // forward definition
typedef struct text_command text_command;
typedef void (*text_command_cb)(text_command *cmd);

// text command handler for registration
struct text_command_handler {
  char *command;
  uint32_t num_positional_args;
  text_command_cb callback;
};

struct text_command {
  char *command;
  char **positional_args;
  uint32_t num_positional_args;
};

struct pt_text_command_parser {
  struct pt *pt;
  uint32_t starting_time;
};

typedef struct {
  text_command_handler handler;
  uint8_t initialized;
} text_command_handler_table_entry;

extern text_command_handler_table_entry text_command_table[TEXT_COMMAND_TABLE_SIZE];

/**
 * Register a command in the command table. It does not check duplication and
 * only the first one will be executed.
 * if the table is full, return COMMAND_FAILED.
 * @param command
 * @param bytes_args
 * @param callback
 * @return
 */
uint8_t text_register_command(char *command,
                              uint32_t num_positional_args,
                              text_command_cb callback);

/**
 * initialize the command parser
 */
void text_init_command();

/**
 * Append data to the command ring buffer. It will yield once each command
 * finished.
 * @param buf
 * @param length
 * @return
 */
void text_feed(uint8_t *buf, uint8_t length);

/**
 * feedback to PC using the format: [COMMAND]: [info]
 *
 * @param command
 * @param info
 */
void text_feedback(const char *command, char *info);

PT_THREAD(task_handle_text_commands(
              struct pt_text_command_parser *pt_text_command_parser));

#endif //STM32_CAMERA_CONTROLLER_TEXT_COMMAND_H
