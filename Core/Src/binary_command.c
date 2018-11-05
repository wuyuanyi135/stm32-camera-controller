/*
 * binary_command.c
 *
 *  Created on: Oct 24, 2018
 *      Author: wuyua
 */
#include <stdlib.h>
#include <usb_device.h>
#include <usbd_cdc_if.h>
#include <usbd_cdc_extension.h>
#include "binary_command.h"
#include "ringbuffer.h"

ring_buffer_t recv_buffer;
command_handler command_table[COMMAND_TABLE_SIZE];

uint8_t register_command(command_t command, uint32_t bytes_args, uint32_t bytes_resp_args, command_cb callback) {
    for (uint32_t i = 0; i < COMMAND_TABLE_SIZE; i++) {
        if (!command_table[i].initialized) {
            // found a empty slot
            command_table[i].bytes_args = bytes_args;
            command_table[i].bytes_resp_args = bytes_resp_args;
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
        if (command_table[i].command == command && command_table[i].initialized == 1) {
            return &command_table[i];
        }
    }
    return 0;
}

void invoke(command_handler* h_command, uint8_t* buf)
{
    if (usbd_cdc_ext_dtr == 1) {
        CDC_Transmit_FS(buf, (uint16_t) h_command->bytes_resp_args + sizeof(command_t));
    }
}

command_t peek_command()
{
    command_t cmd;
    uint8_t* cmd_cursor = &cmd;
    // TODO: combine the peeked values and return the cmd. DONE
    for (ring_buffer_size_t i = 0; i < sizeof(command_t); i++) {
        ring_buffer_peek(&recv_buffer, (char *) (cmd_cursor + i), i);
    }
    return cmd;
}

PT_THREAD(task_handle_commands(
                  struct pt_command_parser *pt_command_parser)) {
    static command_handler *handler;
    static command_t command;
    static uint32_t buffer_size;

    // test timeout
    if (pt_command_parser->starting_time != 0 && HAL_GetTick() - pt_command_parser->starting_time > CMD_RECV_TIMEOUT)
    {
        // timeout occurs, clear all items in the ring buffer
        ring_buffer_dequeue_arr(&recv_buffer, 0, ring_buffer_num_items(&recv_buffer));

        // clear time tick counter
        pt_command_parser->starting_time = 0;

        // reset coroutine execution
        PT_RESTART(pt_command_parser->pt);
    }

    PT_BEGIN(pt_command_parser->pt);

    while (1) {
        // do not check the buffer until something is in it.

        PT_YIELD_UNTIL(pt_command_parser->pt, ring_buffer_num_items(&recv_buffer) >= sizeof(command_t));
        command = peek_command();
        handler = lookup_command(command);
        if (handler == 0) {
            // unrecognized command received. Drop this command.
            ring_buffer_dequeue_arr(&recv_buffer, 0, sizeof(command_t));

            PT_YIELD(pt_command_parser->pt);
        } else {
            // command handler retrieved successfully
            // store the current tick for timeout detection
            pt_command_parser->starting_time = HAL_GetTick();
            // yield until required amount of data is in the receive buffer
            buffer_size = handler->bytes_args + sizeof(command_t);
            PT_YIELD_UNTIL(pt_command_parser->pt, buffer_size <= ring_buffer_num_items(&recv_buffer));

            uint8_t* buffer = malloc(buffer_size);
            if (buffer == NULL)
            {
                // allocation failed, possibly memory leaking or insufficient memory
                // TODO: use indication and logging functions
            }
            else
            {
                ring_buffer_dequeue_arr(&recv_buffer, (char *) buffer, (ring_buffer_size_t) buffer_size);
                handler->callback(handler, buffer+ sizeof (command_t), handler->bytes_args);
                free(buffer);

                // clear tick to prevent raising timeout
                pt_command_parser->starting_time = 0;
            }
        }
    }
    PT_END(pt_command_parser->pt);
}
