#include "common/defines.h"
#include "drivers/io.h"

int main () {
    io_config USER_LED_CONFIG = { IO_A5, 0,  IO_GPIO_OUTPUT, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE };
    io_configure(IO_A5, USER_LED_CONFIG);

    return 0;
} 
