//
// Created by wuyuanyi on 03/11/18.
//

#include "command_test.h"
#ifdef USE_BINARY_COMMAND
#ifdef INCLUDE_TEST_COMMANDS
void test_command_0_cb(command_handler* cmd, uint8_t *buffer, uint32_t length)
{
    uint8_t buf[] = {TEST_COMMAND_0 ,0x50, 0x70};
    invoke(cmd, buf);
}
#endif

void register_test_command()
{
#ifdef INCLUDE_TEST_COMMANDS
    register_command(TEST_COMMAND_0, 0, 2, test_command_0_cb);
#endif
}
#endif