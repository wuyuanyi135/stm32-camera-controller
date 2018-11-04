/*
 * command.h
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */

#ifndef INC_BINARY_COMMAND_H_
#define INC_BINARY_COMMAND_H_

#include "ringbuffer.h"
#include "pt/pt.h"

#define COMMAND_RECV_BUFFER_SIZE 256
#define COMMAND_TABLE_SIZE    32

#undef RING_BUFFER_SIZE
#define RING_BUFFER_SIZE COMMAND_RECV_BUFFER_SIZE

#define COMMAND_OK    1
#define COMMAND_FAILED 0

extern ring_buffer_t recv_buffer;

typedef struct command_handler command_handler;

// the length is redundant but it may be used for future variable-length args.
typedef void (*command_cb)(command_handler* cmd, uint8_t *buffer, uint32_t length);
typedef uint8_t command_t;

typedef struct command_handler {
  command_t command;
  uint32_t bytes_args;
  uint32_t bytes_resp_args;
  command_cb callback;
  uint8_t initialized;
} command_handler;

struct pt_command_parser {
  struct pt *pt;
  uint32_t starting_time;
};

extern command_handler command_table[COMMAND_TABLE_SIZE];

/**
 * Register a command in the command table. It does not check duplication and
 * only the first one will be executed.
 * if the table is full, return COMMAND_FAILED.
 * @param command
 * @param bytes_args
 * @param callback
 * @return
 */
uint8_t register_command(command_t command, uint32_t bytes_args, uint32_t bytes_resp_args, command_cb callback);

/**
 * initialize the command parser
 */
void init_command();

/**
 * Append data to the command ring buffer. It will yield once each command
 * finished.
 * @param buf
 * @param length
 * @return
 */
void feed(uint8_t *buf, uint8_t length);

/**
 * Send command to PC
 * The struct of response packet: 1: the command ID, 2: data segment (length as defined by bytes_resp_args)
 * The command ID must be inserted by the invoker!
 * @param h_command
 * @param buf
 */
void invoke(command_handler* h_command, uint8_t* buf);

PT_THREAD(task_handle_commands(
              struct pt_command_parser *pt_command_parser));

#endif /* INC_BINARY_COMMAND_H_ */
