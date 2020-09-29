//
// Created by wuyuanyi on 31/05/19.
//

#include <stdlib.h>
#include <usb_device.h>
#include <usbd_cdc_if.h>
#include <usbd_cdc_extension.h>
#include "text_command.h"
#include "ringbuffer.h"
#include <string.h>
#include <binary_command.h>

ring_buffer_t text_recv_buffer;
text_command_handler_table_entry text_command_table[TEXT_COMMAND_TABLE_SIZE];

uint8_t text_register_command(char *command,
                              uint32_t num_positional_args,
                              text_command_cb callback) {
  for (uint32_t i = 0; i < TEXT_COMMAND_TABLE_SIZE; i++) {
    if (!text_command_table[i].initialized) {
      // found a empty slot
      text_command_table[i].initialized = 1;

      text_command_handler *p_handler = &text_command_table[i].handler;

      p_handler->callback = callback;
      p_handler->command = strdup(command);

      p_handler->num_positional_args = num_positional_args;

      return TEXT_COMMAND_OK;
    }
  }
  return TEXT_COMMAND_FAILED;
}

void text_init_command() {
  ring_buffer_init(&text_recv_buffer);
}

void text_feed(uint8_t *buf, uint8_t length) {
  ring_buffer_queue_arr(&text_recv_buffer, (const char *) buf, length);
}

text_command_handler *text_lookup_command(char *command) {
  for (int i = 0; i < TEXT_COMMAND_TABLE_SIZE; ++i) {
    if (strcmp(text_command_table[i].handler.command, command) == 0 && text_command_table[i].initialized == 1) {
      return &text_command_table[i].handler;
    }
  }
  return 0;
}

void text_feedback(const char *command, char *info) {
  if (usbd_cdc_ext_dtr == 1) {
    char reply[TEXT_MAX_REPLY_BYTES];
    strcpy(reply, command);
    strcat(reply, ": ");
    strcat(reply, info);
    strcat(reply, "\n");
    CDC_Transmit_FS((u_char *) reply, strlen(reply));
  }
}

void text_parse_and_invoke_command() {
  text_command command;
  char cmd_[TEXT_COMMAND_LENGTH_MAX + 1];
  command.command = cmd_;
  command.num_positional_args = -1;
  command.positional_args = NULL;

  // pop up until line feeder
  char data;
  char data_buf[TEXT_MAX_REPLY_BYTES];
  uint8_t index = 0;
  memset(data_buf, 0, TEXT_MAX_REPLY_BYTES);

  do {
    if (!ring_buffer_dequeue(&text_recv_buffer, &data)) {
      // no data returned, should panic
      return;
    }
    data_buf[index++] = data;
    if (index + 1 >= TEXT_MAX_REPLY_BYTES) {
      text_feedback("~", "invalid command (length)");
      return;
    }
  } while (data != '\n');
  // At this point, the ring buffer has been flushed
  // the last \n should be removed
  data_buf[--index] = 0;

  // extract command token
  char *data_buf_bak = data_buf;
  char *command_token = strtok(data_buf, " ");
  if (!command_token) {
    text_feedback("~", "invalid command");
    return;
  }

  if (strlen(command_token) > TEXT_COMMAND_LENGTH_MAX) {
    text_feedback(command_token, "command too long");
    return;
  }
  strcpy(command.command, command_token);

  // popup the callback function for the command
  text_command_handler *const p_handler = text_lookup_command(command_token);
  if (!p_handler) {
    // unregistered command
    text_feedback(command_token, "unregistered command");
    return;
  }
  command.num_positional_args = p_handler->num_positional_args;

  // parse positional arguments
  if (command.num_positional_args > 0) {
    command.positional_args = malloc(command.num_positional_args * sizeof(char *)); // FREE
    if (!command.positional_args) {
      text_feedback(command_token, "failed to allocate");
      goto EXIT;
    }

    // if more than positional arguments are passed, they are ignored
    for (int i = 0; i < p_handler->num_positional_args; ++i) {
      char *arg_token = strtok(NULL, " ");
      if (!arg_token) {
        text_feedback(command_token, "insufficient args");
        goto EXIT;
      }
      command.positional_args[i] = strdup(arg_token); // FREE
    }
  }

  p_handler->callback(&command);

  // clean up
  EXIT:
  if(command.num_positional_args > 0) {
    for (int i = 0; i < p_handler->num_positional_args; ++i) {
      free(command.positional_args[i]);
    }
    free(command.positional_args);
  }
}

PT_THREAD(task_handle_text_commands(
              struct pt_text_command_parser *pt_text_command_parser)) {

  // no time-out detection

  PT_BEGIN(pt_text_command_parser->pt);

        while (1) {
          // wait for new message
          PT_YIELD_UNTIL(pt_text_command_parser->pt, ring_buffer_num_items(&text_recv_buffer) > 0);

          // wait for line feed (\n)
          while (1) {
            const ring_buffer_size_t numItems = ring_buffer_num_items(&text_recv_buffer);
            for (uint32_t i = 0; i < numItems; i++) {
              char data;
              ring_buffer_peek(&text_recv_buffer, &data, i);
              if (data == '\n')
                // detected line feed, proceed.
                goto BREAK;
            }
            PT_YIELD(pt_text_command_parser->pt);
          }
          BREAK: // line feed detecting loop
          text_parse_and_invoke_command();
        }
  PT_END(pt_text_command_parser->pt);
}
