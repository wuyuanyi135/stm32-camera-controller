/*
 * binary_command.c
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */
#include "binary_command.h"
#include "ringbuffer.h"

ring_buffer_t recv_buffer;
command_handler command_table[COMMAND_TABLE_SIZE];

uint8_t register_command(command_t command, uint32_t bytes_args, command_cb callback) {
  for (uint32_t i = 0; i < COMMAND_TABLE_SIZE; i++) {
    if (!command_table[i].initialized) {
      // found a empty slot
      command_table[i].bytes_args = bytes_args;
      command_table[i].initialized = 1;
      command_table[i].callback = callback;
      command_table[i].command = command;
      return COMMAND_OK;
    }
  }
  return COMMAND_FAILED;
}

void init_command() {
  ring_buffer_init(&recv_buffer);
}

void feed(uint8_t *buf, uint8_t length) {
  ring_buffer_queue_arr(&recv_buffer, (const char *) buf, length);
}

command_handler *lookup_command(command_t command) {
  for (int i = 0; i < COMMAND_TABLE_SIZE; ++i) {
    if (command_table[i].command == command) {
      return &command_table[i];
    }
  }
  return 0;
}

PT_THREAD(task_handle_commands(
              struct pt_command_parser *pt_command_parser)) {
  static command_handler *handler;
  static command_t command;
  PT_BEGIN(pt_command_parser->pt);
        while (1) {
          ring_buffer_peek(&recv_buffer, (char *) &command, sizeof(command_t));
          handler = lookup_command(command);
          if (handler == 0) {
            // unrecognized command received. Drop this command.
            ring_buffer_dequeue_arr(&recv_buffer, 0, sizeof(command_t));
            PT_YIELD(pt_command_parser->pt);
          } else {
            // command handler retrieved successfully

          }
        }
  PT_END(pt_command_parser->pt);
}
