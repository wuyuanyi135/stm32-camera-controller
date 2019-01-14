//
// Created by wuyuanyi on 14/01/19.
//

#include <app.h>

#include "app.h"

void APP_FUNCTION app_init() {

}

void APP_FUNCTION app_test(command_handler *cmd, uint8_t *buffer, uint32_t length) {
  volatile int i;
  i = 0;
  i++;
};

command_handler APP_VARIABLE app_map[] = {
    {
        .command = APP_TEST_COMMAND_0_0,
        .bytes_args = 0,
        .bytes_resp_args = 0,
        .callback = app_test,
        .initialized = 1,
    }
};
uint32_t APP_VARIABLE app_map_size = sizeof(app_map) / sizeof(command_handler);